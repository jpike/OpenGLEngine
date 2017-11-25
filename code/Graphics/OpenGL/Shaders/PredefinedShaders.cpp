#include "Graphics/OpenGL/Shaders/PredefinedShaders.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
namespace SHADERS
{
    const ShaderProgramDescription VERTEX_POSITION_COLOR_SHADER_DESCRIPTION(
        VertexShaderDescription(
            R"(
                // GLSL 1.50.
                #version 150

                in vec3 object_space_position;
                in vec4 vertex_color;
        
                uniform mat4 world_transform;
                uniform mat4 view_transform;
                uniform mat4 projection_transform;

                out vec4 output_vertex_color;

                void main()
                {
                    output_vertex_color = vertex_color;
                    output_vertex_color.a = 1.0;
                    gl_Position = projection_transform * view_transform * world_transform * vec4(object_space_position, 1.0);
                }
            )",
            VertexSizeInBytesFromTypeAndComponentCount<float>(7),
            {
                VertexShaderInputVariable("object_space_position", VertexShaderInputVariableComponentCount(3), VertexShaderInputVariableByteOffsetToFirstComponent(0)),
                VertexShaderInputVariable("vertex_color", VertexShaderInputVariableComponentCount(4), VertexShaderInputVariableByteOffsetToFirstComponent(3 * sizeof(float))),
            }),
        FragmentShaderDescription(
            R"(
                // GLSL 1.50.
                #version 150

                // The input color from the vertex shader.
                in vec4 output_vertex_color;

                // The final output color.
                out vec4 output_color;

                void main()
                {
                    output_color = output_vertex_color;
                    output_color.a = 1.0;
                }
            )",
            "output_color")
        );
}
}
}
