#pragma once

#include <memory>
#include <vector>
#include <gl/GL.h>
#include <Windows.h>
#include "Graphics/OpenGL/OpenGL.h"
#include "Graphics/OpenGL/Shaders/ShaderProgram.h"
#include "Graphics/OpenGL/Shaders/ShaderProgramDescription.h"
#include "Graphics/OpenGL/VertexBuffer.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
    /// Represents a device for rendering graphics using OpenGL.
    /// @note   Currently only supports up to OpenGL 4.2.0.
    class GraphicsDevice
    {
    public:
        // CONSTRUCTION.
        static std::shared_ptr<GraphicsDevice> Create(const HDC device_context);
        explicit GraphicsDevice(const HDC device_context, const HGLRC open_gl_render_context);
        ~GraphicsDevice();

        // VERTEX BUFFER METHODS.
        std::shared_ptr<VertexBuffer> CreateVertexBuffer();
        void Bind(const VertexBuffer& vertex_buffer);

        // SHADER METHODS.
        std::shared_ptr<SHADERS::ShaderProgram> CreateShaderProgram(const SHADERS::ShaderProgramDescription& shader_program_description);
        void Use(const SHADERS::ShaderProgram& shader_program);

        // PUBLIC MEMBER VARIABLES FOR EASY ACCESS.
        /// The regular Windows device context.
        HDC DeviceContext;

    private:
        // SHADER METHODS.
        GLuint CompileShader(const GLenum shader_type, const std::string& source_code);

        // MEMBER VARIABLES.
        /// The OpenGL rendering context.
        HGLRC OpenGLRenderContext;
        /// All vertex buffers allocated on the device.
        std::vector< std::shared_ptr<VertexBuffer> > VertexBuffers;
        /// All shader programs allocated on the device.
        std::vector< std::shared_ptr<SHADERS::ShaderProgram> > ShaderPrograms;
    };
}
}
