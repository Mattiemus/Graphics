#include "SDL.h"

#include "Engine/Graphics/Shader.hpp"

#include <fstream>

using namespace std;

Shader::Shader(unsigned int shaderId, GLenum shaderType)
    : _shaderId(shaderId), _shaderType(shaderType)
{
}

Shader::~Shader()
{
    glDeleteShader(_shaderId);
}

Shader* Shader::fromFile(const char* file, GLenum shaderType)
{
    // Create a new shader
    unsigned int shaderId = glCreateShader(shaderType);
    
    // Load the full file
    ifstream fileStream(file);
    string fileContents((istreambuf_iterator<char>(fileStream)), istreambuf_iterator<char>());
    const char* fileBuf = fileContents.data();
    int fileSize = fileContents.size();
    fileStream.clear();

    // Store and compile the shader
    glShaderSource(shaderId, 1, &fileBuf, &fileSize);
    glCompileShader(shaderId);

    // Make sure it compiled
    GLint success = GL_FALSE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        // Get the error log
        GLint logSize = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

        // Grab the error
        char* errorBuffer = new char[logSize];
        glGetShaderInfoLog(shaderId, logSize, &logSize, errorBuffer);

        // Delete the shader and throw an exception
        glDeleteShader(shaderId);
        throw exception(errorBuffer);
    }

    return new Shader(shaderId, shaderType);
}