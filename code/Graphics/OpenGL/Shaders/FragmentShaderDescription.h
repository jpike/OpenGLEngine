#pragma once

#include <string>

namespace GRAPHICS
{
namespace OPEN_GL
{
namespace SHADERS
{
    /// A description of a fragment shader.
    struct FragmentShaderDescription
    {
        // PUBLIC MEMBER VARIABLES FOR EASY ACCESS.
        /// The uncompiled source code of the fragment shader.
        std::string UncompiledCode;
        /// The name of the output color variable of the fragment shader.
        std::string OutputColorVariableName;

        // CONSTRUCTION.
        // A constructor requiring all member variables is defined to make
        // specification of shaders easier (i.e. construction can be done
        // in one line as opposed to needing to set member variables on
        // separate lines).
        explicit FragmentShaderDescription(
            const std::string& uncompiled_code,
            const std::string& output_color_variable_name);
    };
}
}
}
