#include "Graphics/OpenGL/Shaders/VertexShaderInputVariable.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
namespace SHADERS
{
    /// Constructor.
    /// @param[in]  name - The name of the variable.
    /// @param[in]  component_count - The number of components that the variable can hold.
    /// @param[in]  byte_offset_to_first_component - The number of bytes from the start of
    ///     the vertex data to the first component of this variable.
    VertexShaderInputVariable::VertexShaderInputVariable(
        const std::string& name,
        const int component_count,
        const uint64_t byte_offset_to_first_component) :
    Name(name),
    ComponentCount(component_count),
    ByteOffsetToFirstComponent(byte_offset_to_first_component)
    {}
}
}
}
