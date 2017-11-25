#include "Graphics/Vertex.h"

namespace GRAPHICS
{
    /// Constructor to create a vertex without texture coordinates.
    /// @param[in]  object_space_position - The 3D position of the vertex in object space.
    /// @param[in]  color - The color of the vertex.
    Vertex::Vertex(
        const MATH::Vector3f& object_space_position,
        const GRAPHICS::Color& color) :
    ObjectSpacePosition(object_space_position),
    Color(color)
    {}
}
