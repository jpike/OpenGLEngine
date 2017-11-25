#pragma once

#include <vector>
#include "Graphics/OpenGL/OpenGL.h"
#include "Graphics/OpenGL/Shaders/VertexShaderInputVariable.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
namespace SHADERS
{
    /// A vertex shader that has been compiled and allocated on a graphics device.
    class VertexShader
    {
    public:
        // CONSTRUCTION.
        explicit VertexShader(
            const GLuint id,
            const unsigned int vertex_size_in_bytes,
            const std::vector<VertexShaderInputVariable>& input_variables);

        // PUBLIC MEMBER VARIABLES FOR EASY ACCESS.
        /// The ID of the vertex shader.
        GLuint Id;
        /// The size of each vertex, in bytes.
        unsigned int VertexSizeInBytes;
        /// All of the input variables to the vertex shader.
        std::vector<VertexShaderInputVariable> InputVariables;
    };
}
}
}
