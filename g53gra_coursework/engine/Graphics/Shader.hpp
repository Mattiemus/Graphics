#ifndef ENGINE_GRAPHICS_SHADER_HPP
#define ENGINE_GRAPHICS_SHADER_HPP

#include "Engine/Core/GL.hpp"

class Shader
{
    friend class ShaderProgram;

public:
    Shader(const Shader &other) = delete;
    ~Shader();

    static Shader* fromFile(const char* file, GLenum shaderType);

    Shader &operator =(const Shader &other) = delete;

private:
    Shader(unsigned int shaderId, GLenum shaderType);

    unsigned int _shaderId;
    GLenum _shaderType;
};

#endif