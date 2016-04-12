#include "Engine/Graphics/ShaderProgram.hpp"
#include "Engine/Core/GL.hpp"

using namespace std;

ShaderProgram::ShaderProgram()
    : _programId(0), _linked(false)
{
    _programId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    // Clear and delete all shaders
    for (auto it = _shaders.begin(); it != _shaders.end(); ++it) {
        delete (*it);
    }
    _shaders.clear();

    glDeleteProgram(_programId);
}

void ShaderProgram::use()
{
    if (!_linked) {
        throw exception("Cannot use unliked shader program");
    }
    glUseProgram(_programId);
}

void ShaderProgram::link()
{
    if (_linked) {
        throw exception("Cannot re-link shader program");
    }
    glLinkProgram(_programId);
    _linked = true;

    // Check we linked correctly
    GLint success = GL_FALSE;
    glGetProgramiv(_programId, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        // Get the error log
        GLint logSize = 0;
        glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &logSize);

        // Grab the error
        char* errorBuffer = new char[logSize];
        glGetProgramInfoLog(_programId, logSize, &logSize, errorBuffer);

        // Throw
        throw exception(errorBuffer);
    }

    // Validate the program
    validate();

    // Store the locations of all unforms (optimisation)
    int count;
    glGetProgramiv(_programId, GL_ACTIVE_UNIFORMS, &count);
    for (int i = 0; i < count; i++) {
        // Get the uniform name
        int maxNameLength = 255;
        char name[256];
        int nameLength;
        int size;
        GLenum type;
        glGetActiveUniform(_programId, i, maxNameLength, &nameLength, &size, &type, name);

        // Trim the name if we need too
        string nameString(name);
        if (nameString.find('[') != string::npos) {
            nameString = nameString.substr(0, nameString.find('['));
        }

        // Get and insert its location into the uniform map.
        int location = glGetUniformLocation(_programId, name);
        _unformLocations.insert(make_pair(nameString, location));
    }
}

void ShaderProgram::attachShader(Shader* shader)
{
    if (_linked) {
        throw exception("Cannot attach more shaders once shader program is linked");
    }

    glAttachShader(_programId, shader->_shaderId);
    _shaders.push_back(shader);
}

void ShaderProgram::validate()
{
    // Validate
    glValidateProgram(_programId);
    GLint validationSuccess = GL_FALSE;
    glGetProgramiv(_programId, GL_VALIDATE_STATUS, &validationSuccess);
    if (validationSuccess == GL_FALSE) {
        throw exception("Could not validate shader program");
    }
}

void ShaderProgram::setParameter(const char* paramName, bool value)
{
    int location = _unformLocations[paramName];
    glProgramUniform1i(_programId, location, value ? 1 : 0);
}

void ShaderProgram::setParameter(const char* paramName, int value)
{
    int location = _unformLocations[paramName];
    glProgramUniform1i(_programId, location, value);
}

void ShaderProgram::setParameter(const char* paramName, float value)
{
    int location = _unformLocations[paramName];
    glProgramUniform1f(_programId, location, value);
}

void ShaderProgram::setParameter(const char* paramName, const Vector2 &vec2)
{
    int location = _unformLocations[paramName];
    glProgramUniform2f(_programId, location, vec2.x, vec2.y);
}

void ShaderProgram::setParameter(const char* paramName, const Vector3 &vec3)
{
    int location = _unformLocations[paramName];
    glProgramUniform3f(_programId, location, vec3.x, vec3.y, vec3.z);
}

void ShaderProgram::setParameter(const char* paramName, const vector<float> &floats)
{
    float* floatArray = new float[floats.size()];
    for (size_t i = 0; i < floats.size(); i++) {
        floatArray[i] = floats[i];
    }

    int location = _unformLocations[paramName];
    glProgramUniform1fv(_programId, location, floats.size(), floatArray);
    
    delete[] floatArray;
}

void ShaderProgram::setParameter(const char* paramName, const vector<Vector3> &vec3)
{
    float* vec3Array = new float[vec3.size() * 3];
    for (size_t i = 0; i < vec3.size(); i++) {
        vec3Array[(i * 3) + 0] = vec3[i].x;
        vec3Array[(i * 3) + 1] = vec3[i].y;
        vec3Array[(i * 3) + 2] = vec3[i].z;
    }

    int location = _unformLocations[paramName];
    glProgramUniform3fv(_programId, location, vec3.size(), vec3Array);

    delete[] vec3Array;
}

void ShaderProgram::setParameter(const char* paramName, const vector<Vector4> &vec4)
{
    float* vec4Array = new float[vec4.size() * 4];
    for (size_t i = 0; i < vec4.size(); i++) {
        vec4Array[(i * 4) + 0] = vec4[i].x;
        vec4Array[(i * 4) + 1] = vec4[i].y;
        vec4Array[(i * 4) + 2] = vec4[i].z;
        vec4Array[(i * 4) + 3] = vec4[i].w;
    }

    int location = _unformLocations[paramName];
    glProgramUniform4fv(_programId, location, vec4.size(), vec4Array);

    delete[] vec4Array;
}

void ShaderProgram::setParameter(const char* paramName, const Matrix4x4 &mat)
{
    float matrix[] {
        mat.m11, mat.m12, mat.m13, mat.m14,
        mat.m21, mat.m22, mat.m23, mat.m24,
        mat.m31, mat.m32, mat.m33, mat.m34,
        mat.m41, mat.m42, mat.m43, mat.m44
    };

    int location = _unformLocations[paramName];
    glProgramUniformMatrix4fv(_programId, location, 1, GL_FALSE, matrix);
}
