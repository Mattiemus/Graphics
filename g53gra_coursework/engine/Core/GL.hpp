#ifndef ENGINE_CORE_GL_HPP
#define ENGINE_CORE_GL_HPP

#include "Engine/Math/Matrix4x4.hpp"

#include "SDL_opengl.h"

// TODO: https://www.opengl.org/registry/

/*
* Extensions
*/

extern "C" PFNGLCREATESHADERPROC glCreateShader;
extern "C" PFNGLDELETESHADERPROC glDeleteShader;
extern "C" PFNGLSHADERSOURCEPROC glShaderSource;
extern "C" PFNGLCOMPILESHADERPROC glCompileShader;
extern "C" PFNGLGETSHADERIVPROC glGetShaderiv;
extern "C" PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

extern "C" PFNGLGENBUFFERSPROC glGenBuffers;
extern "C" PFNGLBINDBUFFERPROC glBindBuffer;
extern "C" PFNGLBUFFERDATAPROC glBufferData;

extern "C" PFNGLVALIDATEPROGRAMPROC glValidateProgram;
extern "C" PFNGLCREATEPROGRAMPROC glCreateProgram;
extern "C" PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern "C" PFNGLATTACHSHADERPROC glAttachShader;
extern "C" PFNGLDETACHSHADERPROC glDetachShader​;
extern "C" PFNGLUSEPROGRAMPROC glUseProgram;
extern "C" PFNGLLINKPROGRAMPROC glLinkProgram;
extern "C" PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

extern "C" PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern "C" PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
extern "C" PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1i;
extern "C" PFNGLPROGRAMUNIFORM1FPROC glProgramUniform1f;
extern "C" PFNGLPROGRAMUNIFORM2FPROC glProgramUniform2f;
extern "C" PFNGLPROGRAMUNIFORM3FPROC glProgramUniform3f;
extern "C" PFNGLPROGRAMUNIFORM1FVPROC glProgramUniform1fv;
extern "C" PFNGLPROGRAMUNIFORM3FVPROC glProgramUniform3fv;
extern "C" PFNGLPROGRAMUNIFORM4FVPROC glProgramUniform4fv;
extern "C" PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fv;
extern "C" PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern "C" PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;

extern "C" PFNGLACTIVETEXTUREPROC glActiveTexture;

extern "C" PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern "C" PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

extern "C" PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
extern "C" PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
extern "C" PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture;
extern "C" PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;

#endif