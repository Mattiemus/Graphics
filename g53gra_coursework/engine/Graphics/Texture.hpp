#ifndef ENGINE_GRAPHICS_TEXTURE_HPP
#define ENGINE_GRAPHICS_TEXTURE_HPP

#include "Engine/Core/GL.hpp"

class Texture
{
public:
    Texture(const Texture &other) = delete;
    ~Texture();

    static Texture* fromFile(const char* file);
    static float* heightsFromFile(const char* file, unsigned int &width, unsigned int &height);

    void bind(GLenum textureLocation);

    Texture &operator =(const Texture &other) = delete;

private:
    Texture(int textureId);

    unsigned int _textureId;
};

#endif