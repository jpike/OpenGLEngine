#include "Graphics/OpenGL/Shaders/FragmentShader.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
namespace SHADERS
{
    /// Constructor.
    /// @param[in]  id - The ID of the fragment shader.
    /// @param[in]  output_color_variable_name - The name of the output color variable of the fragment shader.
    FragmentShader::FragmentShader(const GLuint id, const std::string& output_color_variable_name) :
        Id(id),
        OutputColorVariableName(output_color_variable_name)
    {}
}
}
}
