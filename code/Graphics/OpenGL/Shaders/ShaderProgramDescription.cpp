#include "Graphics/OpenGL/Shaders/ShaderProgramDescription.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
namespace SHADERS
{
    /// Constructor.
    /// @param[in]  vertex_shader - The description of the vertex shader.
    /// @param[in]  fragment_shader - The description of the fragment shader.
    ShaderProgramDescription::ShaderProgramDescription(
        const VertexShaderDescription& vertex_shader,
        const FragmentShaderDescription& fragment_shader) :
    VertexShader(vertex_shader),
    FragmentShader(fragment_shader)
    {}
}
}
}
