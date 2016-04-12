#include "Engine/Core/GL.hpp"

PFNGLCREATESHADERPROC glCreateShader = nullptr;
PFNGLDELETESHADERPROC glDeleteShader = nullptr;
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;

PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
PFNGLBUFFERDATAPROC glBufferData = nullptr;

PFNGLVALIDATEPROGRAMPROC glValidateProgram = nullptr;
PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
PFNGLATTACHSHADERPROC glAttachShader = nullptr;
PFNGLDETACHSHADERPROC glDetachShader​ = nullptr;
PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;

PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = nullptr;
PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1i = nullptr;
PFNGLPROGRAMUNIFORM1FPROC glProgramUniform1f = nullptr;
PFNGLPROGRAMUNIFORM2FPROC glProgramUniform2f = nullptr;
PFNGLPROGRAMUNIFORM3FPROC glProgramUniform3f = nullptr;
PFNGLPROGRAMUNIFORM3FVPROC glProgramUniform1fv = nullptr;
PFNGLPROGRAMUNIFORM3FVPROC glProgramUniform3fv = nullptr;
PFNGLPROGRAMUNIFORM4FVPROC glProgramUniform4fv = nullptr;
PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fv = nullptr;
PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = nullptr;

PFNGLACTIVETEXTUREPROC glActiveTexture = nullptr;

PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;

PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = nullptr;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = nullptr;
PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture = nullptr;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = nullptr;