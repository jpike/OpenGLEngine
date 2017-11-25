#include "Graphics/OpenGL/GraphicsDevice.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
    /// Attempts to crete a graphics device using OpenGL for the provided window.
    /// @param[in]  device_context - The handle to the device context for which the graphics device
    ///     should be created.
    /// @return The graphics device, if successfully created; null otherwise.
    std::shared_ptr<GraphicsDevice> GraphicsDevice::Create(const HDC device_context)
    {
        // CREATE THE OPEN GL RENDERING CONTEXT.
        const HGLRC NO_CONTEXT_TO_SHARE_WITH = nullptr;
        const int context_attribute_list[] =
        {
            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
            ATTRIBUTE_LIST_TERMINATOR
        };
        HGLRC open_gl_render_context = wglCreateContextAttribsARB(device_context, NO_CONTEXT_TO_SHARE_WITH, context_attribute_list);
        BOOL open_gl_context_made_current = wglMakeCurrent(device_context, open_gl_render_context);
        if (!open_gl_context_made_current)
        {
            return nullptr;
        }
        
        // CREATE THE GRAPHICS DEVICE.
        std::shared_ptr<GraphicsDevice> graphics_device = std::make_shared<GraphicsDevice>(
            device_context,
            open_gl_render_context);
        return graphics_device;
    }

    /// Constructor.
    /// @param[in]  device_context - The regular Windows device context.
    /// @param[in]  open_gl_render_context - The OpenGL rendering context.
    GraphicsDevice::GraphicsDevice(const HDC device_context, const HGLRC open_gl_render_context) :
        DeviceContext(device_context),
        OpenGLRenderContext(open_gl_render_context),
        VertexBuffers(),
        ShaderPrograms()
    {}

    /// Destructor that deletes resources and the OpenGL rendering context for the device.
    GraphicsDevice::~GraphicsDevice()
    {
        // DELETE SHADER PROGRAMS.
        for (const auto& shader_program : ShaderPrograms)
        {
            // MAKE SURE THE SHADER PROGRAM EXISTS.
            bool shader_program_exists = (nullptr != shader_program);
            if (!shader_program_exists)
            {
                // Continue trying to delete other shader programs that still exist.
                continue;
            }

            // DELETE THE SHADER PROGRAM.
            glDeleteProgram(shader_program->Id);

            // DELETE SHADERS IN THE PROGRAM.
            glDeleteShader(shader_program->FragmentShader.Id);
            glDeleteShader(shader_program->VertexShader.Id);
        }

        // DELETE VERTEX BUFFERS/ARRAYS.
        for (const auto& vertex_buffer : VertexBuffers)
        {
            // MAKE SURE THE VERTEX BUFFER EXISTS.
            bool vertex_buffer_exists = (nullptr != vertex_buffer);
            if (!vertex_buffer_exists)
            {
                // Continue trying to delete other vertex buffers that still exist.
                continue;
            }

            // DELETE THE VERTEX BUFFER.
            const GLsizei ONE_BUFFER = 1;
            glDeleteBuffers(ONE_BUFFER, &vertex_buffer->BufferId);

            // DELETE THE VERTEX ARRAY.
            const GLsizei ONE_ARRAY = 1;
            glDeleteBuffers(ONE_ARRAY, &vertex_buffer->ArrayId);
        }

        // DELETE THE RENDERING CONTEXT.
        wglDeleteContext(OpenGLRenderContext);
    }

    /// Creates a vertex buffer.
    /// @return A new vertex buffer, if successfully created; null otherwise.
    std::shared_ptr<VertexBuffer> GraphicsDevice::CreateVertexBuffer()
    {
        // ALLOCATE A VERTEX ARRAY.
        const GLsizei ONE_VERTEX_ARRAY = 1;
        GLuint array_id = INVALID_ID;
        glGenVertexArrays(ONE_VERTEX_ARRAY, &array_id);

        // ALLOCATE A VERTEX BUFFER.
        const GLsizei ONE_VERTEX_BUFFER = 1;
        GLuint buffer_id = INVALID_ID;
        glGenBuffers(ONE_VERTEX_BUFFER, &buffer_id);

        // CREATE AND STORE THE VERTEX BUFFER.
        std::shared_ptr<VertexBuffer> vertex_buffer = std::make_shared<VertexBuffer>(array_id, buffer_id);
        VertexBuffers.push_back(vertex_buffer);
        return vertex_buffer;
    }

    /// Binds a vertex buffer for current use.
    /// @param[in]  vertex_buffer - The vertex buffer to bind.
    void GraphicsDevice::Bind(const VertexBuffer& vertex_buffer)
    {
        glBindVertexArray(vertex_buffer.ArrayId);
    }

    /// Creates a shader program from the provided description.
    /// @param[in]  shader_program_description - A description of the shader program to create.
    /// @return The shader program based on the description, if successfully created; null otherwise.
    std::shared_ptr<SHADERS::ShaderProgram> GraphicsDevice::CreateShaderProgram(const SHADERS::ShaderProgramDescription& shader_program_description)
    {
        // COMPILE THE VERTEX SHADER.
        GLuint vertex_shader_id = CompileShader(
            GL_VERTEX_SHADER,
            shader_program_description.VertexShader.UncompiledCode);
        SHADERS::VertexShader vertex_shader(
            vertex_shader_id,
            shader_program_description.VertexShader.VertexSizeInBytes,
            shader_program_description.VertexShader.InputVariables);

        // COMPILE THE FRAGMENT SHADER.
        GLuint fragment_shader_id = CompileShader(
            GL_FRAGMENT_SHADER,
            shader_program_description.FragmentShader.UncompiledCode);
        SHADERS::FragmentShader fragment_shader(fragment_shader_id, shader_program_description.FragmentShader.OutputColorVariableName);

        // ATTACH THE SHADERS TO A SHADER PROGRAM.
        GLuint shader_program_id = glCreateProgram();
        std::shared_ptr<SHADERS::ShaderProgram> shader_program = std::make_shared<SHADERS::ShaderProgram>(
            shader_program_id, 
            vertex_shader, 
            fragment_shader);

        // SET THE FRAGMENT SHADER'S OUTPUT COLOR VARIABLE.
        shader_program->SetFragmentShaderOutputColorVariable();

        // LINK THE SHADER PROGRAM.
        glLinkProgram(shader_program->Id);

        // STORE AND RETURN THE SHADER PROGRAM.
        ShaderPrograms.push_back(shader_program);
        return shader_program;
    }

    /// Sets the graphics device to use the provided shader program.
    /// @param[in]  shader_program - The shader program to use.
    void GraphicsDevice::Use(const SHADERS::ShaderProgram& shader_program)
    {
        // SET THE INPUT VARIABLES FOR THE PROGRAM.
        shader_program.SetVertexInputs();
        
        // SET THE PROGRAM AS THE CURRENT ONE.
        glUseProgram(shader_program.Id);
    }

    /// Attempts to compile a shader.
    /// @param[in]  shader_type - The type of shader being compiled.
    /// @param[in]  source_code - The shader source code to compile.
    /// @return The shader ID, if successfully compiled; INVALID_ID otherwise.
    GLuint GraphicsDevice::CompileShader(const GLenum shader_type, const std::string& source_code)
    {
        // CREATE THE SHADER.
        GLuint shader = glCreateShader(shader_type);
        bool shader_created = (INVALID_ID != shader);
        if (!shader_created)
        {
            return INVALID_ID;
        }

        // SET THE SOURCE CODE FOR THE SHADER.
        const GLsizei SINGLE_SOURCE_CODE_STRING = 1;
        const GLint* const SOURCE_CODE_IS_NULL_TERMINATED = NULL;
        const char* source_code_text = source_code.c_str();
        glShaderSource(
            shader,
            SINGLE_SOURCE_CODE_STRING,
            &source_code_text,
            SOURCE_CODE_IS_NULL_TERMINATED);

        // COMPILE THE SHADER.
        glCompileShader(shader);

        // CHECK IF COMPILATION SUCCEEDED.
        GLint shader_compile_status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compile_status);
        bool shader_compiled = (GL_TRUE == shader_compile_status);
        if (shader_compiled)
        {
            return shader;
        }
        else
        {
            // GET THE SHADER COMPILER ERROR.
            const GLsizei LEGNTH_OF_LOG_NOT_NEEDED = NULL;
            char shader_compile_log_buffer[512];
            glGetShaderInfoLog(
                shader,
                sizeof(shader_compile_log_buffer) / sizeof(shader_compile_log_buffer[0]),
                LEGNTH_OF_LOG_NOT_NEEDED,
                shader_compile_log_buffer);
            /// @todo   Log via a better mechanism.
            OutputDebugString("Shader compile error: ");
            OutputDebugString(shader_compile_log_buffer);

            // INDICATE THAT THE SHADER COULD NOT BE CREATED.
            return INVALID_ID;
        }
    }
}
}
