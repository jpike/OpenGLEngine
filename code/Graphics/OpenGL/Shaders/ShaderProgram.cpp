#include "Graphics/OpenGL/Shaders/ShaderProgram.h"

namespace GRAPHICS
{
namespace OPEN_GL
{
namespace SHADERS
{
    /// Constructor.  The shaders are attached to this program.
    /// @param[in]  id - The ID of the shader program.
    /// @param[in]  vertex_shader - The vertex shader.
    /// @param[in]  fragment_shader - The fragment shader.
    ShaderProgram::ShaderProgram(const GLuint id, const SHADERS::VertexShader& vertex_shader, const SHADERS::FragmentShader& fragment_shader) :
        Id(id),
        VertexShader(vertex_shader),
        FragmentShader(fragment_shader)
    {
        glAttachShader(Id, vertex_shader.Id);
        glAttachShader(Id, fragment_shader.Id);
    }

    /// Sets the fragment shader output color variable.
    /// Should be called before linking.
    void ShaderProgram::SetFragmentShaderOutputColorVariable() const
    {
        const GLuint ONLY_COLOR_OUTPUT = 0;
        glBindFragDataLocation(
            Id,
            ONLY_COLOR_OUTPUT,
            FragmentShader.OutputColorVariableName.c_str());
    }

    /// Sets all vertex shader input variables to the program.
    /// Should be called each time before rendering.
    void ShaderProgram::SetVertexInputs() const
    {
        for (const auto& input_variable : VertexShader.InputVariables)
        {
            SetVertexInput(
                input_variable,
                VertexShader.VertexSizeInBytes);
        }
    }

    /// Sets the specified vertex shader input variable to the program.
    /// @param[in]  input_variable - The input variable to set.
    /// @param[in]  vertex_size_in_bytes - The size of 1 vertex to the program, in bytes.
    void ShaderProgram::SetVertexInput(
        const VertexShaderInputVariable& input_variable,
        const unsigned int vertex_size_in_bytes) const
    {
        // GET THE ID OF THE INPUT VARIABLE IN THE PROGRAM.
        GLint vertex_input_variable_id = glGetAttribLocation(Id, input_variable.Name.c_str());

        // DEFINE THE SPECIFICATION OF THE INPUT VARIABLE.
        glVertexAttribPointer(
            vertex_input_variable_id,
            input_variable.ComponentCount,
            GL_FLOAT,
            GL_FALSE,
            vertex_size_in_bytes,
            (void*)input_variable.ByteOffsetToFirstComponent);

        // ENABLE THE VERTEX INPUT VARIABLE.
        glEnableVertexAttribArray(vertex_input_variable_id);
    }

    /// Sets the values for the specified uniform matrix variable.
    /// @param[in]  uniform_matrix_variable_name - The name of the uniform variable for the matrix.
    /// @param[in]  matrix - The matrix whose values to set in the uniform variable.
    void ShaderProgram::SetUniformMatrix(
        const std::string& uniform_matrix_variable_name,
        const MATH::Matrix4x4f& matrix) const
    {
        // GET THE UNIFORM MATRIX VARIABLE.
        GLint matrix_variable = glGetUniformLocation(Id, uniform_matrix_variable_name.c_str());

        // GET THE MATRIX ELEMENT VALUES IN ROW-MAJOR ORDER.
        const float* matrix_elements_in_row_major_order = matrix.ElementsInRowMajorOrder();

        // SET THE MATRIX VALUES IN THE UNIFORM VARIABLE.
        const GLsizei ONE_MATRIX = 1;
        const GLboolean ROW_MAJOR_ORDER = GL_TRUE;
        glUniformMatrix4fv(matrix_variable, ONE_MATRIX, ROW_MAJOR_ORDER, matrix_elements_in_row_major_order);
    }
}
}
}
