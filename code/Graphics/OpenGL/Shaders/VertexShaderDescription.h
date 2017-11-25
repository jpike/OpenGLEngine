#pragma once

#include <initializer_list>
#include <string>
#include <vector>
#include "Graphics/OpenGL/Shaders/VertexShaderInputVariable.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
namespace SHADERS
{
    /// A description of a vertex shader.
    struct VertexShaderDescription
    {
        // PUBLIC MEMBER VARIABLES FOR EASY ACCESS.
        /// The uncompiled source code of the vertex shader.
        std::string UncompiledCode;
        /// The size of each vertex, in bytes.
        unsigned int VertexSizeInBytes;
        /// All of the input variables to the vertex shader.
        std::vector<VertexShaderInputVariable> InputVariables;

        // CONSTRUCTION.
        // A constructor requiring all member variables is defined to make
        // specification of shaders easier (i.e. construction can be done
        // in one line as opposed to needing to set member variables on
        // separate lines).
        explicit VertexShaderDescription(
            const std::string& uncompiled_code,
            const unsigned int vertex_size_in_bytes,
            const std::initializer_list<VertexShaderInputVariable>& input_variables);
    };
}
}
}
