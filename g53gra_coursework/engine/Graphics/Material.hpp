#ifndef ENGINE_GRAPHICS_MATERIAL_HPP
#define ENGINE_GRAPHICS_MATERIAL_HPP

#include "Engine/Graphics/ShaderProgram.hpp"
#include "Engine/Graphics/Texture.hpp"
#include "Engine/Graphics/Texture.hpp"
#include "Engine/Scene/SceneObject.hpp"

#include <map>
#include <string>

enum class MaterialEngineValue
{
    MODEL_MATIRX,
    VIEW_MATRIX,
    PROJECTION_MATIRX,
    TOTAL_TIME
};

class Material 
{
public:
    Material(ShaderProgram* shader);
    Material(const Material &other) = delete;
    ~Material();

    static Material* createLitMaterial(const char* diffuseMapSampler, const char* normalMapSampler, const char* specularMapSampler);
    static Material* createLitParallaxMaterial(const char* diffuseMapSampler, const char* normalMapSampler, const char* specularMapSampler, const char* heightMapSampler);
    static Material* createLeavesMaterial(const char* diffuseMapSampler);
    static Material* createGrassMaterial(const char* diffuseMapSampler);
    static Material* createFireMaterial(const char* diffuseMapSampler);
    static Material* createSkyboxMaterial(const char* diffuseMapSampler);

    bool getUseLighting() const
    {
        return _useLighting;
    }

    void setUseLighting(bool value)
    {
        _useLighting = value;
    }

    void connectEngineParameter(const char* paramName, MaterialEngineValue value);
    void connectTextureParameter(const char* paramName, Texture* value);
    void connectParameter(const char* paramName, bool value);
    void connectParameter(const char* paramName, int value);
    void connectParameter(const char* paramName, const Vector2 &value);
    void connectParameter(const char* paramName, const Vector3 &value);

    void draw(const Matrix4x4 &modelMatrix, float totalTime);

    Material &operator =(const Material &other) = delete;

private:
    ShaderProgram* _shader;
    bool _useLighting;
    std::map<std::string, MaterialEngineValue> _engineValues;
    std::map<std::string, Texture*> _textureValues;
    std::map<std::string, bool> _boolValues;
    std::map<std::string, int> _intValues;
    std::map<std::string, Vector2> _vec2Values;
    std::map<std::string, Vector3> _vec3Values;
};

#endif