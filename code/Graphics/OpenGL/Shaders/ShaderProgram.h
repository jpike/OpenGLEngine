#pragma once

#include <string>
#include <gl/GL.h>
#include "Graphics/OpenGL/Shaders/FragmentShader.h"
#include "Graphics/OpenGL/Shaders/VertexShader.h"
#include "Math/Matrix4x4.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
/// Holds code related to OpenGL shaders.
namespace SHADERS
{
    /// A shader program consisting of 1 vertex shader and 1 fragment shader.
    /// Only shader programs with 1 vertex and 1 fragment shader are supported
    /// since more advanced kinds of shader programs are not yet needed.
    class ShaderProgram
    {
    public:
        // CONSTRUCTION.
        explicit ShaderProgram(const GLuint id, const VertexShader& vertex_shader, const FragmentShader& fragment_shader);

        // OTHER PUBLIC METHODS.
        void SetFragmentShaderOutputColorVariable() const;
        void SetVertexInputs() const;
        void SetUniformMatrix(
            const std::string& uniform_matrix_variable_name, 
            const MATH::Matrix4x4f& matrix) const;

        // PUBLIC MEMBER VARIABLES FOR EASY ACCESS.
        /// The ID of the shader program.
        GLuint Id;
        /// The vertex shader.
        class VertexShader VertexShader;
        /// The fragment shader.
        class FragmentShader FragmentShader;

    private:
        // PRIVATE METHODS.
        void SetVertexInput(
            const VertexShaderInputVariable& input_variable,
            const unsigned int vertex_size_in_bytes) const;
    };
}
}
}
