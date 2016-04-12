#ifndef ENGINE_GRAPHICS_SHADERPROGRAM_HPP
#define ENGINE_GRAPHICS_SHADERPROGRAM_HPP

#include "Engine/Graphics/Shader.hpp"
#include "Engine/Graphics/Texture.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Vector4.hpp"
#include "Engine/Math/Matrix4x4.hpp"

#include <vector>
#include <string>
#include <map>

class ShaderProgram
{
public:
    ShaderProgram();
    ShaderProgram(const ShaderProgram &other) = delete;
    ~ShaderProgram();

    void use();
    void link();
    void attachShader(Shader* shader);
    void validate();

    void setParameter(const char* paramName, bool value);
    void setParameter(const char* paramName, int value);
    void setParameter(const char* paramName, float value);
    void setParameter(const char* paramName, const Vector2 &vec2);
    void setParameter(const char* paramName, const Vector3 &vec3);
    void setParameter(const char* paramName, const std::vector<float> &floats);
    void setParameter(const char* paramName, const std::vector<Vector3> &vec3);
    void setParameter(const char* paramName, const std::vector<Vector4> &vec4);
    void setParameter(const char* paramName, const Matrix4x4 &mat);

    ShaderProgram &operator =(const ShaderProgram &other) = delete;

private:
    unsigned int _programId;
    bool _linked;
    std::vector<const Shader*> _shaders;
    std::map<std::string, int> _unformLocations;
};

#endif