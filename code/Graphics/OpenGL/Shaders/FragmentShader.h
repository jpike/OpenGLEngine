#pragma once

#include <string>
#include <gl/GL.h>

namespace GRAPHICS
{
namespace OPEN_GL
{
namespace SHADERS
{
    /// A fragment shader that has been compiled and allocated on a graphics device.
    class FragmentShader
    {
    public:
        // CONSTRUCTION.
        explicit FragmentShader(const GLuint id, const std::string& output_color_variable_name);

        // PUBLIC MEMBER VARIABLES FOR EASY ACCESS.
        /// The ID of the fragment shader.
        GLuint Id;
        /// The name of the output color variable of the fragment shader.
        std::string OutputColorVariableName;
    };
}
}
}
