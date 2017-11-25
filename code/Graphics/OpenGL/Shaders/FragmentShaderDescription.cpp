#include "Graphics/OpenGL/Shaders/FragmentShaderDescription.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
namespace SHADERS
{
    /// Constructor.
    /// @param[in]  uncompiled_code - The uncompiled source code of the fragment shader.
    /// @param[in]  output_color_variable_name - The name of the output color variable of the fragment shader.
    FragmentShaderDescription::FragmentShaderDescription(
        const std::string& uncompiled_code,
        const std::string& output_color_variable_name) :
    UncompiledCode(uncompiled_code),
    OutputColorVariableName(output_color_variable_name)
    {}
}
}
}
