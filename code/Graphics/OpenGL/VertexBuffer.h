#pragma once

#include <vector>
#include "Graphics/OpenGL/OpenGL.h"
#include "Graphics/Vertex.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
    /// A buffer on a graphics device for holding vertices.
    /// This class holds both OpenGL vertex array and buffer IDs
    /// since it's easier to think of them together when thinking
    /// about how vertices get passed to graphics hardware,
    /// and any additional flexibility for keeping them separate
    /// has not yet been needed.
    class VertexBuffer
    {
    public:
        // CONSTRUCTION.
        explicit VertexBuffer(const GLuint array_id, const GLuint buffer_id);

        // PUBLIC METHODS.
        void Fill(const std::vector<GRAPHICS::Vertex>& vertices) const;

        // PUBLIC MEMBER VARIABLES FOR EASY ACCESS.
        /// The ID of the vertex array associated with this buffer.
        GLuint ArrayId;
        /// The ID of the vertex buffer.
        GLuint BufferId;
    };
}
}
