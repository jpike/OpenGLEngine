#pragma once

#include <cstdint>
#include <string>

namespace GRAPHICS
{
namespace OPEN_GL
{
namespace SHADERS
{
    /// Describes a variable that is input to a vertex shader.
    struct VertexShaderInputVariable
    {
        // PUBLIC MEMBER VARIABLES FOR EASY ACCESS.
        /// The name of the variable.
        std::string Name;
        /// The number of components that the variable can hold.
        /// For example, a vec3 has 3 components.
        int ComponentCount;
        /// The number of bytes from the start of the vertex data
        /// to the first component of this variable.  For example,
        /// if this variable is right after the first input variable
        /// to a vertex shader that is a floating-point vec3, this offset
        /// should be 3 * sizeof(float).
        uint64_t ByteOffsetToFirstComponent;

        // CONSTRUCTION.
        // A constructor requiring all member variables is defined to make
        // specification of shaders easier (i.e. construction can be done
        // in one line as opposed to needing to set member variables on
        // separate lines).
        explicit VertexShaderInputVariable(
            const std::string& name,
            const int component_count,
            const uint64_t byte_offset_to_first_component);
    };
}
}
}
