#pragma once

#include <cstddef>
#include <memory>
#include <gl/GL.h>
#include <Windows.h>
#include <ThirdParty/OpenGL/glext.h>
#include <ThirdParty/OpenGL/wglext.h>

namespace GRAPHICS
{
/// Holds code related to the OpenGL graphics API.
namespace OPEN_GL
{
    /// The value that marks the end of an OpenGL attribute list.
    const int ATTRIBUTE_LIST_TERMINATOR = 0;
    /// The value for the name of a non-existent OpenGL object.
    const int NO_OBJECT_NAME = 0;
    const GLuint INVALID_ID = 0;

    /// The Initialize function should be called once to load OpenGL functions.
    bool Initialize(const HDC device_context);

    extern PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
    extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
    extern PFNGLGENBUFFERSPROC glGenBuffers;
    extern PFNGLBINDBUFFERPROC glBindBuffer;
    extern PFNGLBUFFERDATAPROC glBufferData;
    extern PFNGLCREATESHADERPROC glCreateShader;
    extern PFNGLSHADERSOURCEPROC glShaderSource;
    extern PFNGLCOMPILESHADERPROC glCompileShader;
    extern PFNGLGETSHADERIVPROC glGetShaderiv;
    extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
    extern PFNGLCREATEPROGRAMPROC glCreateProgram;
    extern PFNGLATTACHSHADERPROC glAttachShader;
    extern PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation;
    extern PFNGLLINKPROGRAMPROC glLinkProgram;
    extern PFNGLUSEPROGRAMPROC glUseProgram;
    extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
    extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
    extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
    extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
    extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
    extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
    extern PFNGLDELETESHADERPROC glDeleteShader;
    extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
    extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
    extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
    extern PFNGLUNIFORM3FPROC glUniform3f;
    extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
}
}
