#pragma once

#include "Graphics/OpenGL/Shaders/FragmentShaderDescription.h"
#include "Graphics/OpenGL/Shaders/VertexShaderDescription.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
namespace SHADERS
{
    /// A description of a shader program.
    /// Only shader programs with 1 vertex and 1 fragment shader are supported
    /// since more advanced kinds of shader programs are not yet needed.
    struct ShaderProgramDescription
    {
        // PUBLIC MEMBER VARIABLES FOR EASY ACCESS.
        /// The description of the vertex shader.
        VertexShaderDescription VertexShader;
        /// The description of the fragment shader.
        FragmentShaderDescription FragmentShader;

        // CONSTRUCTION.
        // A constructor requiring all member variables is defined to make
        // specification of shaders easier (i.e. construction can be done
        // in one line as opposed to needing to set member variables on
        // separate lines).
        explicit ShaderProgramDescription(
            const VertexShaderDescription& vertex_shader,
            const FragmentShaderDescription& fragment_shader);
    };
}
}
}
