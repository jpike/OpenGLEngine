#pragma once

#include "Graphics/OpenGL/Shaders/ShaderProgramDescription.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
namespace SHADERS
{
    /// Calculates a vertex size (for use in shader vertex attributes).
    /// @tparam VertexComponentType - The type of each vertex component (for example, float).
    /// @param[in]  vertex_component_count - The number of components per vertex.
    ///     For example, if a vertex only has x, y, and z positional coordinates,
    ///     this value would be 3.
    /// @return The size (in bytes) of 1 vertex with the specified parameters.
    /// @todo   Upgrade to Visual Studio 2015 so that this can be made constexpr.
    template <typename VertexComponentType>
    unsigned int VertexSizeInBytesFromTypeAndComponentCount(const unsigned int vertex_component_count)
    {
        unsigned int vertex_component_size_in_bytes = sizeof(VertexComponentType);
        unsigned int vertex_size_in_bytes = vertex_component_count * vertex_component_size_in_bytes;
        return vertex_size_in_bytes;
    }

    /// A type alias to make specification of a vertex shader input variable's component count clearer.
    using VertexShaderInputVariableComponentCount = int;
    /// A type alias to make specification of a vertex shader input variable's byte offset to the first component clearer.
    using VertexShaderInputVariableByteOffsetToFirstComponent = unsigned int;

    /// A description of a shader program that accepts vertices with position and color attributes.
    extern const ShaderProgramDescription VERTEX_POSITION_COLOR_SHADER_DESCRIPTION;
}
}
}
