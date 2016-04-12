#include "Engine/Graphics/Material.hpp"
#include "Engine/Core/Engine.hpp"
#include "Engine/Graphics/Camera.hpp"

using namespace std;

Material::Material(ShaderProgram* shader)
    : _shader(shader), _useLighting(false)
{
}

Material::~Material()
{
}

Material* Material::createLitMaterial(const char* diffuseMapSampler, const char* normalMapSampler, const char* specularMapSampler)
{
    // Load the basic lighting shaders, and link them into a program
    ShaderProgram* program = new ShaderProgram();
    program->attachShader(Shader::fromFile("./Assets/Shaders/lighting.vert.fx", GL_VERTEX_SHADER));
    program->attachShader(Shader::fromFile("./Assets/Shaders/lighting.frag.fx", GL_FRAGMENT_SHADER));
    program->link();
    program->use();

    // Create a material, and attach all its parameters
    Material* material = new Material(program);
    material->setUseLighting(true);
    material->connectEngineParameter("modelMatrix", MaterialEngineValue::MODEL_MATIRX);
    material->connectEngineParameter("viewMatrix", MaterialEngineValue::VIEW_MATRIX);
    material->connectEngineParameter("projectionMatrix", MaterialEngineValue::PROJECTION_MATIRX);
    material->connectParameter("textureRepeat", Vector2(1.0f, 1.0f));
    material->connectTextureParameter("diffuseMapSampler", Texture::fromFile(diffuseMapSampler));
    material->connectTextureParameter("normalMapSampler", Texture::fromFile(normalMapSampler));
    material->connectTextureParameter("specularMapSampler", Texture::fromFile(specularMapSampler));
    return material;
}

Material* Material::createLitParallaxMaterial(const char* diffuseMapSampler, const char* normalMapSampler, const char* specularMapSampler, const char* heightMapSampler)
{
    // Load the basic lighting shaders, and link them into a program
    ShaderProgram* program = new ShaderProgram();
    program->attachShader(Shader::fromFile("./Assets/Shaders/lighting_parallax.vert.fx", GL_VERTEX_SHADER));
    program->attachShader(Shader::fromFile("./Assets/Shaders/lighting_parallax.frag.fx", GL_FRAGMENT_SHADER));
    program->link();
    program->use();

    // Create a material, and attach all its parameters
    Material* material = new Material(program);
    material->setUseLighting(true);
    material->connectEngineParameter("modelMatrix", MaterialEngineValue::MODEL_MATIRX);
    material->connectEngineParameter("viewMatrix", MaterialEngineValue::VIEW_MATRIX);
    material->connectEngineParameter("projectionMatrix", MaterialEngineValue::PROJECTION_MATIRX);
    material->connectParameter("textureRepeat", Vector2(1.0f, 1.0f));
    material->connectTextureParameter("diffuseMapSampler", Texture::fromFile(diffuseMapSampler));
    material->connectTextureParameter("normalMapSampler", Texture::fromFile(normalMapSampler));
    material->connectTextureParameter("specularMapSampler", Texture::fromFile(specularMapSampler));
    material->connectTextureParameter("heightMapSampler", Texture::fromFile(heightMapSampler));
    return material;
}

Material* Material::createLeavesMaterial(const char* diffuseMapSampler)
{
    // Load the basic lighting shaders, and link them into a program
    ShaderProgram* program = new ShaderProgram();
    program->attachShader(Shader::fromFile("./Assets/Shaders/leaves.vert.fx", GL_VERTEX_SHADER));
    program->attachShader(Shader::fromFile("./Assets/Shaders/leaves.frag.fx", GL_FRAGMENT_SHADER));
    program->link();
    program->use();

    // Create a material, and attach all its parameters
    Material* material = new Material(program);
    material->setUseLighting(true);
    material->connectEngineParameter("modelMatrix", MaterialEngineValue::MODEL_MATIRX);
    material->connectEngineParameter("viewMatrix", MaterialEngineValue::VIEW_MATRIX);
    material->connectEngineParameter("projectionMatrix", MaterialEngineValue::PROJECTION_MATIRX);
    material->connectEngineParameter("totalTime", MaterialEngineValue::TOTAL_TIME);
    material->connectParameter("textureRepeat", Vector2(1.0f, 1.0f));
    material->connectTextureParameter("diffuseMapSampler", Texture::fromFile(diffuseMapSampler));
    return material;
}

Material* Material::createGrassMaterial(const char* diffuseMapSampler)
{
    // Load the basic lighting shaders, and link them into a program
    ShaderProgram* program = new ShaderProgram();
    program->attachShader(Shader::fromFile("./Assets/Shaders/grass.vert.fx", GL_VERTEX_SHADER));
    program->attachShader(Shader::fromFile("./Assets/Shaders/grass.frag.fx", GL_FRAGMENT_SHADER));
    program->link();
    program->use();

    // Create a material, and attach all its parameters
    Material* material = new Material(program);
    material->setUseLighting(true);
    material->connectEngineParameter("modelMatrix", MaterialEngineValue::MODEL_MATIRX);
    material->connectEngineParameter("viewMatrix", MaterialEngineValue::VIEW_MATRIX);
    material->connectEngineParameter("projectionMatrix", MaterialEngineValue::PROJECTION_MATIRX);
    material->connectEngineParameter("totalTime", MaterialEngineValue::TOTAL_TIME);
    material->connectParameter("textureRepeat", Vector2(1.0f, 1.0f));
    material->connectTextureParameter("diffuseMapSampler", Texture::fromFile(diffuseMapSampler));
    return material;
}

Material* Material::createFireMaterial(const char* diffuseMapSampler)
{
    // Load the basic lighting shaders, and link them into a program
    ShaderProgram* program = new ShaderProgram();
    program->attachShader(Shader::fromFile("./Assets/Shaders/fire.vert.fx", GL_VERTEX_SHADER));
    program->attachShader(Shader::fromFile("./Assets/Shaders/fire.frag.fx", GL_FRAGMENT_SHADER));
    program->link();
    program->use();

    // Create a material, and attach all its parameters
    Material* material = new Material(program);
    material->setUseLighting(true);
    material->connectEngineParameter("modelMatrix", MaterialEngineValue::MODEL_MATIRX);
    material->connectEngineParameter("viewMatrix", MaterialEngineValue::VIEW_MATRIX);
    material->connectEngineParameter("projectionMatrix", MaterialEngineValue::PROJECTION_MATIRX);
    material->connectEngineParameter("totalTime", MaterialEngineValue::TOTAL_TIME);
    material->connectParameter("textureRepeat", Vector2(1.0f, 1.0f));
    material->connectTextureParameter("diffuseMapSampler", Texture::fromFile(diffuseMapSampler));
    return material;
}

Material* Material::createSkyboxMaterial(const char* diffuseMapSampler)
{
    // Load the basic lighting shaders, and link them into a program
    ShaderProgram* program = new ShaderProgram();
    program->attachShader(Shader::fromFile("./Assets/Shaders/sky.vert.fx", GL_VERTEX_SHADER));
    program->attachShader(Shader::fromFile("./Assets/Shaders/sky.frag.fx", GL_FRAGMENT_SHADER));
    program->link();
    program->use();

    // Create a material, and attach all its parameters
    Material* material = new Material(program);
    material->setUseLighting(false);
    material->connectEngineParameter("modelMatrix", MaterialEngineValue::MODEL_MATIRX);
    material->connectEngineParameter("viewMatrix", MaterialEngineValue::VIEW_MATRIX);
    material->connectEngineParameter("projectionMatrix", MaterialEngineValue::PROJECTION_MATIRX);
    material->connectTextureParameter("diffuseMapSampler", Texture::fromFile(diffuseMapSampler));
    return material;
}

void Material::connectEngineParameter(const char* paramName, MaterialEngineValue value)
{
    auto it = _engineValues.find(paramName); 
    if (it == _engineValues.end()) {
        _engineValues.insert(make_pair(paramName, value));
    } else {
        _engineValues[paramName] = value;
    }    
}

void Material::connectTextureParameter(const char* paramName, Texture* value)
{
    auto it = _textureValues.find(paramName);
    if (it == _textureValues.end()) {
        _textureValues.insert(make_pair(paramName, value));
    } else {
        _textureValues[paramName] = value;
    }
}

void Material::connectParameter(const char* paramName, bool value)
{
    auto it = _boolValues.find(paramName);
    if (it == _boolValues.end()) {
        _boolValues.insert(make_pair(paramName, value));
    } else {
        _boolValues[paramName] = value;
    }
}

void Material::connectParameter(const char* paramName, int value)
{
    auto it = _intValues.find(paramName);
    if (it == _intValues.end()) {
        _intValues.insert(make_pair(paramName, value));
    } else {
        _intValues[paramName] = value;
    }
}

void Material::connectParameter(const char* paramName, const Vector2 &value)
{
    auto it = _vec2Values.find(paramName);
    if (it == _vec2Values.end()) {
        _vec2Values.insert(make_pair(paramName, value));
    } else {
        _vec2Values[paramName] = value;
    }
}

void Material::connectParameter(const char* paramName, const Vector3 &value)
{
    auto it = _vec3Values.find(paramName);
    if (it == _vec3Values.end()) {
        _vec3Values.insert(make_pair(paramName, value));
    } else {
        _vec3Values[paramName] = value;
    }
}

void Material::draw(const Matrix4x4 &modelMatrix, float totalTime)
{
    // Use the shader
    _shader->use();

    // Set the engine values
    for (pair<std::string, MaterialEngineValue> engineValue : _engineValues) {
        if (engineValue.second == MaterialEngineValue::MODEL_MATIRX) {
            _shader->setParameter(engineValue.first.c_str(), modelMatrix);
        } 
        if (engineValue.second == MaterialEngineValue::VIEW_MATRIX) {
            _shader->setParameter(engineValue.first.c_str(), Engine::getInstance().getCamera()->getView());
        } 
        if (engineValue.second == MaterialEngineValue::PROJECTION_MATIRX) {
            _shader->setParameter(engineValue.first.c_str(), Engine::getInstance().getCamera()->getProjection());
        }
        if (engineValue.second == MaterialEngineValue::TOTAL_TIME) {
            _shader->setParameter(engineValue.first.c_str(), totalTime);
        }
    }

    // Set the texture values
    int texture = 0;
    for (pair<std::string, Texture*> textureValue : _textureValues) {
        _shader->setParameter(textureValue.first.c_str(), texture);
        textureValue.second->bind(GL_TEXTURE0 + texture);
        texture++;
    }

    // Set other parameters
    for (pair<std::string, bool> value : _boolValues) {
        _shader->setParameter(value.first.c_str(), value.second);
    }
    for (pair<std::string, int> value : _intValues) {
        _shader->setParameter(value.first.c_str(), value.second);
    }
    for (pair<std::string, Vector2> value : _vec2Values) {
        _shader->setParameter(value.first.c_str(), value.second);
    }
    for (pair<std::string, Vector3> value : _vec3Values) {
        _shader->setParameter(value.first.c_str(), value.second);
    }

    // Use any lights
    if (_useLighting) {
        // Collate all the lights into vectors for the shader
        vector<Vector3> lightPositions; lightPositions.reserve(Engine::getInstance().getLights().size());
        vector<Vector4> lightAmbients; lightAmbients.reserve(Engine::getInstance().getLights().size());
        vector<Vector4> lightColor; lightColor.reserve(Engine::getInstance().getLights().size());
        vector<float> lightPower; lightPower.reserve(Engine::getInstance().getLights().size());
        for (Light* light : Engine::getInstance().getLights()) {
            lightPositions.push_back(light->getPosition());
            lightAmbients.push_back(light->getAmbientColor());
            lightColor.push_back(light->getColor());
            lightPower.push_back(light->getPower());
        }

        // Send to the shader
        _shader->setParameter("lightPosition_worldspace", lightPositions);
        _shader->setParameter("lightAmbient", lightAmbients);
        _shader->setParameter("lightColor", lightColor);
        _shader->setParameter("lightPower", lightPower);
    }
}

