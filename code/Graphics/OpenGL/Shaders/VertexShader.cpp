#include "Graphics/OpenGL/Shaders/VertexShader.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
namespace SHADERS
{
    /// Constructor.
    /// @param[in]  id - The ID of the vertex shader.
    /// @param[in]  vertex_size_in_bytes - The size of each vertex, in bytes.
    /// @param[in]  input_variables - All of the input variables to the vertex shader.
    VertexShader::VertexShader(
        const GLuint id,
        const unsigned int vertex_size_in_bytes,
        const std::vector<VertexShaderInputVariable>& input_variables) :
    Id(id),
    VertexSizeInBytes(vertex_size_in_bytes),
    InputVariables(input_variables)
    {}
}
}
}
