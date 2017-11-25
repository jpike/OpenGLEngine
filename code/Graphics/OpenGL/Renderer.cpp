#include "ErrorHandling/NullChecking.h"
#include "Graphics/OpenGL/Renderer.h"
#include "Graphics/OpenGL/Shaders/PredefinedShaders.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
    /// Attempts to create a renderer that uses the provided graphics device.
    /// @param[in]  graphics_device - The graphics device to use for rendering.
    /// @return A renderer, if successfully created; null otherwise.
    std::unique_ptr<Renderer> Renderer::Create(const std::shared_ptr<OPEN_GL::GraphicsDevice>& graphics_device)
    {
        // MAKE SURE A GRAPHICS DEVICE WAS PROVIDED.
        bool graphics_device_exists = (nullptr != graphics_device);
        if (!graphics_device_exists)
        {
            // A renderer cannot be created without a graphics device.
            return nullptr;
        }

        // CREATE THE DEFAULT SHADER PROGRAMS.
        std::shared_ptr<SHADERS::ShaderProgram> position_color_shader_program = graphics_device->CreateShaderProgram(
            SHADERS::VERTEX_POSITION_COLOR_SHADER_DESCRIPTION);
        bool shader_program_created = (nullptr != position_color_shader_program);
        if (!shader_program_created)
        {
            // A renderer cannot be creted without this shader program.
            return nullptr;
        }

        // CREATE THE RENDERER.
        std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(
            graphics_device,
            position_color_shader_program);
        return renderer;
    }

    /// Constructor.
    /// @param[in]  graphics_device - The graphics device to use for rendering.
    /// @param[in]  position_color_shader_program - The shader program for rendering
    ///     objects with position and color vertex attributes.
    /// @throws std::exception - Thrown if a parameter is null.
    Renderer::Renderer(
        const std::shared_ptr<OPEN_GL::GraphicsDevice>& graphics_device,
        const std::shared_ptr<SHADERS::ShaderProgram>& position_color_shader_program) :
    GraphicsDevice(graphics_device),
    PositionColorShaderProgram(position_color_shader_program),
    VertexBuffers(),
    Camera()
    {
        // MAKE SURE REQUIRED PARAMETERS WERE PROVIDED.
        ERROR_HANDLING::ThrowInvalidArgumentExceptionIfNull(
            GraphicsDevice,
            "Graphics device cannot be null for renderer.");
        ERROR_HANDLING::ThrowInvalidArgumentExceptionIfNull(
            PositionColorShaderProgram,
            "Position-color shader program cannot be null for renderer.");
    }

    /// Clears the screen to the specified color.
    /// Additional buffers for the screen are also cleared.
    /// @param[in]  color - The color to clear the screen to.
    void Renderer::ClearScreen(const GRAPHICS::Color& color) const
    {
        // SET THE COLOR TO CLEAR THE SCREEN TO.
        glClearColor(color.Red, color.Green, color.Blue, color.Alpha);

        // CLEAR THE SCREEN'S BUFFERS.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /// Draws a 3D object.
    /// @param[in]  object_3D - The 3D object to draw.
    void Renderer::Draw(const GRAPHICS::Object3D& object_3D)
    {
        // CHECK IF A VERTEX BUFFER ALREADY EXISTS FOR THIS OBJECT.
        auto previously_allocated_vertex_buffer = VertexBuffers.find(&object_3D);
        bool vertex_buffer_already_exists = (VertexBuffers.cend() != previously_allocated_vertex_buffer);
        if (!vertex_buffer_already_exists)
        {
            // CREATE NEW VERTEX BUFFER WITH THIS OBJECT'S VERTICES.
            std::shared_ptr<VertexBuffer> new_vertex_buffer = GraphicsDevice->CreateVertexBuffer();
            bool vertex_buffer_created = (nullptr != new_vertex_buffer);
            if (vertex_buffer_created)
            {
                // FILL THE BUFFER WITH THIS OBJECT'S VERTICES.
                new_vertex_buffer->Fill(object_3D.Vertices);

                // STORE THE VERTEX BUFFER FOR THIS 3D OBJECT.
                VertexBuffers[&object_3D] = new_vertex_buffer;
            }
        }
        
        // GET THE VERTEX BUFFER FOR THE OBJECT.
        std::shared_ptr<VertexBuffer> vertex_buffer = VertexBuffers[&object_3D];
        bool vertex_buffer_exists = (nullptr != vertex_buffer);
        if (!vertex_buffer_exists)
        {
            // The buffer is required for rendering.
            return;
        }

        // SET THE SHADER PROGRAM TO BE USED.
        GraphicsDevice->Use(*PositionColorShaderProgram);
   
        // BIND THE VERTEX ARRAY BUFFER FOR RENDERING.
        GraphicsDevice->Bind(*vertex_buffer);

        // SET THE TRANSFORMATION MATRICES.
        MATH::Matrix4x4f world_transform = object_3D.WorldTransform();
        PositionColorShaderProgram->SetUniformMatrix("world_transform", world_transform);

        MATH::Matrix4x4f camera_view_transform = Camera.ViewTransform();
        PositionColorShaderProgram->SetUniformMatrix("view_transform", camera_view_transform);

        /// @todo   Figure out how we want to put projections into camera class.
        const float LEFT_X_WORLD_BOUNDARY = Camera.WorldPosition.X - 1.0f;
        const float RIGHT_X_WORLD_BOUNDARY = Camera.WorldPosition.X + 1.0f;
        const float BOTTOM_Y_WORLD_BOUNDARY = Camera.WorldPosition.Y - 1.0f;
        const float TOP_Y_WORLD_BOUNDARY = Camera.WorldPosition.Y + 1.0f;
        const float NEAR_Z_WORLD_BOUNDARY = Camera.WorldPosition.Z - 0.5f;
        const float FAR_Z_WORLD_BOUNDARY = Camera.WorldPosition.Z - 2.5f;
        MATH::Matrix4x4f orthographic_projection_transform = Camera::OrthographicProjection(
            LEFT_X_WORLD_BOUNDARY,
            RIGHT_X_WORLD_BOUNDARY,
            BOTTOM_Y_WORLD_BOUNDARY,
            TOP_Y_WORLD_BOUNDARY,
            NEAR_Z_WORLD_BOUNDARY,
            FAR_Z_WORLD_BOUNDARY);
        PositionColorShaderProgram->SetUniformMatrix("projection_transform", orthographic_projection_transform);

        const MATH::Angle<float>::Degrees VERTICAL_FIELD_OF_VIEW_IN_DEGREES(60.0f);
        const float ASPECT_RATIO_WIDTH_OVER_HEIGHT = 1.0f;
        MATH::Matrix4x4f perspective_projection_transform = Camera::PerspectiveProjection(
            VERTICAL_FIELD_OF_VIEW_IN_DEGREES,
            ASPECT_RATIO_WIDTH_OVER_HEIGHT,
            NEAR_Z_WORLD_BOUNDARY,
            FAR_Z_WORLD_BOUNDARY);
        //PositionColorShaderProgram->SetUniformMatrix("projection_transform", perspective_projection_transform);

        // DRAW THE 3D OBJECT'S VERTICES.
        const unsigned int FIRST_VERTEX = 0;
        GLsizei vertex_count = static_cast<GLsizei>(object_3D.Vertices.size());
        glDrawArrays(GL_TRIANGLES, FIRST_VERTEX, vertex_count);
    }

    /// Displays the screen to the user by swapping the back buffer
    /// with the front buffer.
    void Renderer::DisplayScreen() const
    {
        SwapBuffers(GraphicsDevice->DeviceContext);
    }
}
}
