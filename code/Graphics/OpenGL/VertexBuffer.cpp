#include "Graphics/OpenGL/VertexBuffer.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
    /// Constructor.
    /// @param[in]  array_id - The ID of the vertex array associated with this buffer.
    /// @param[in]  buffer_id - The ID of the vertex buffer.
    VertexBuffer::VertexBuffer(const GLuint array_id, const GLuint buffer_id) :
        ArrayId(array_id),
        BufferId(buffer_id)
    {};

    /// Fills this vertex buffer with the data in the provided vertices.
    /// @param[in]  vertices - The vertices to place in the buffer.
    void VertexBuffer::Fill(const std::vector<GRAPHICS::Vertex>& vertices) const
    {
        // CONVERT THE VERTICES TO A RAW DATA FORMAT THAT CAN BE PLACED IN THE BUFFER.
        std::vector<float> vertex_data;
        for (const auto& vertex : vertices)
        {
            vertex_data.push_back(vertex.ObjectSpacePosition.X);
            vertex_data.push_back(vertex.ObjectSpacePosition.Y);
            vertex_data.push_back(vertex.ObjectSpacePosition.Z);
            vertex_data.push_back(vertex.Color.Red);
            vertex_data.push_back(vertex.Color.Green);
            vertex_data.push_back(vertex.Color.Blue);
            vertex_data.push_back(vertex.Color.Alpha);
        }

        // FILL THE BUFFER WITH THE VERTEX DATA.
        GLsizeiptr vertex_data_size_in_bytes = sizeof(float) * vertex_data.size();
        glBindBuffer(GL_ARRAY_BUFFER, BufferId);
        glBufferData(GL_ARRAY_BUFFER, vertex_data_size_in_bytes, vertex_data.data(), GL_STATIC_DRAW);
    }
}
}
