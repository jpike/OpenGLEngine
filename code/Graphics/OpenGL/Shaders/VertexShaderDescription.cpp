#include "Graphics/OpenGL/Shaders/VertexShaderDescription.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
namespace SHADERS
{
    /// Constructor.
    /// @param[in]  uncompiled_code - The uncompiled source code of the vertex shader.
    /// @param[in]  vertex_size_in_bytes - The size of each vertex, in bytes.
    /// @param[in]  input_variables - All of the input variables to the vertex shader.
    VertexShaderDescription::VertexShaderDescription(
        const std::string& uncompiled_code,
        const unsigned int vertex_size_in_bytes,
        const std::initializer_list<VertexShaderInputVariable>& input_variables) :
    UncompiledCode(uncompiled_code),
    VertexSizeInBytes(vertex_size_in_bytes),
    InputVariables(input_variables)
    {}
}
}
}
