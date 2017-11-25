#pragma once

#include <memory>
#include "Graphics/Color.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

/// Holds code related to computer graphics.
///
/// Coordinate systems in this namespace follow the following conventions:
/// - Object space - Coordinates are expressed relative to the local coordinate
///     system of an object.  Also known as model space.
/// - World space - Coordinates are expressed relative to the entire world
///     being represented.
/// - Camera space - Coordinates expressed relative to the camera viewing
///     the world.  Also known as eye space.
/// - Clip space - Coordinates expressed as normalized device coordinates
///     within the canonical view volume.
/// - Screen space - Coordinates expressed as 2D pixel positions on a screen.
///
/// The following terms are used to refer to transformations between spaces:
/// - World transform - Transforms coordinates from object space to world space.
///     Also known as a model transform.
/// - View transform - Transforms coordinates from world space to camera space.
///     Also known as a camera or eye transform.
/// - Projection transform - Transforms coordinates from camera space to clip space.
/// - Viewport transform - Transforms coordinates from clip space to screen space.
namespace GRAPHICS
{
    /// A vertex for a point.  At a minimum, a vertex is required
    /// to have a 3D position and color.  Other attributes are
    /// optional.
    class Vertex
    {
    public:
        // CONSTRUCTION.
        explicit Vertex(
            const MATH::Vector3f& object_space_position, 
            const GRAPHICS::Color& color);

        // PUBLIC MEMBER VARIABLES FOR EASY ACCESS.
        /// The 3D position of the vertex in object space.
        /// Only 3D positions are supported since they're the most common
        /// use case.  2D positions can be mimicked by always setting the
        /// z coordinate to a constant value.
        MATH::Vector3f ObjectSpacePosition = MATH::Vector3f();
        /// The color of the vertex.
        GRAPHICS::Color Color = GRAPHICS::Color();
        /// Optional texture coordinates of the vertex.
        /// Null if no texture coordinates are associated with the vertex.
        //std::unique_ptr<MATH::Vector2f> TextureCoordinates = nullptr;
    };
}
