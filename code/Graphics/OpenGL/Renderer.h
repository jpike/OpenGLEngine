#pragma once

#include <memory>
#include <unordered_map>
#include "Graphics/Camera.h"
#include "Graphics/Color.h"
#include "Graphics/Object3D.h"
#include "Graphics/OpenGL/GraphicsDevice.h"
#include "Graphics/OpenGL/OpenGL.h"
#include "Graphics/OpenGL/Shaders/ShaderProgram.h"
#include "Graphics/OpenGL/VertexBuffer.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
    /// A renderer that uses OpenGL.
    class Renderer
    {
    public:
        // CONSTRUCTION.
        static std::unique_ptr<Renderer> Create(const std::shared_ptr<OPEN_GL::GraphicsDevice>& graphics_device);
        explicit Renderer(
            const std::shared_ptr<OPEN_GL::GraphicsDevice>& graphics_device,
            const std::shared_ptr<SHADERS::ShaderProgram>& position_color_shader_program);

        // RENDERING.
        void ClearScreen(const GRAPHICS::Color& color) const;
        void Draw(const GRAPHICS::Object3D& object_3D);
        void DisplayScreen() const;

        // PUBLIC MEMBER VARIABLES FOR EASY ACCESS.
        /// The camera for viewing 3D scenes that get rendered.
        GRAPHICS::Camera Camera;

    private:
        // MEMBER VARIABLES.
        /// The graphics device to use for rendering.
        std::shared_ptr<OPEN_GL::GraphicsDevice> GraphicsDevice;
        /// The shader program for rendering objects with position and color vertex attributes.
        std::shared_ptr<SHADERS::ShaderProgram> PositionColorShaderProgram;
        /// A mapping of 3D objects to their associated vertex buffers.
        /// @todo   How to free memory when a 3D object is no longer needed?
        std::unordered_map< const GRAPHICS::Object3D*, std::shared_ptr<VertexBuffer> > VertexBuffers;
    };
}
}
