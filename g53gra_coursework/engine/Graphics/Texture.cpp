#include "SDL.h"

#include "Engine/Graphics/Texture.hpp"
#include "Engine/Core/GL.hpp"

#include <exception>
#include <iostream>

using namespace std;

Texture::Texture(int textureId)
    : _textureId(textureId)
{
}

Texture::~Texture()
{
    glDeleteTextures(1, &_textureId);
}

Texture* Texture::fromFile(const char* file)
{
    // Load a texture using SDL
    SDL_Surface* textureImage = SDL_LoadBMP(file);
    if (textureImage != nullptr) {
        // Create the texture
        unsigned int texId;
        glGenTextures(1, &texId);

        // Bind and store the texture data
        glBindTexture(GL_TEXTURE_2D, texId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
            textureImage->w, textureImage->h, 0, 
            GL_BGR, GL_UNSIGNED_BYTE, textureImage->pixels);

        // Ensure that we loaded the texture correctly
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            glDeleteTextures(1, &texId);
            throw exception("Failed to upload data to texture");
        }

        // Setup the texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // We are done with the surface, we can now free it
        SDL_FreeSurface(textureImage);

        // Return the created texture
        return new Texture(texId);
    } else {
        throw exception("Failed to load SDL surface");
    }
}

float* Texture::heightsFromFile(const char* file, unsigned int &width, unsigned int &height)
{
    // Load a texture using SDL
    SDL_Surface* textureImage = SDL_LoadBMP(file);
    if (textureImage != nullptr) {
        // Create a buffer for the heights
        float* heights = new float[textureImage->w * textureImage->h];

        // Read the height at the specified coordinates
        int bpp = textureImage->format->BytesPerPixel;
        for (int x = 0; x < textureImage->w; x++) {
            for (int y = 0; y < textureImage->h; y++) {
                // Read and store the pixel
                Uint8* pixel8 = static_cast<Uint8*>(textureImage->pixels) + y * textureImage->pitch + x * bpp;
                heights[y * textureImage->h + x] = static_cast<float>(*pixel8) / 255.0f;
            }
        }

        // We are done with the surface, we can now free it
        SDL_FreeSurface(textureImage);

        // Return the created texture
        width = textureImage->w;
        height = textureImage->h;
        return heights;
    }
    else {
        throw exception("Failed to load SDL surface");
    }
}

void Texture::bind(GLenum textureLocation)
{
    glActiveTexture(textureLocation);
    glBindTexture(GL_TEXTURE_2D, _textureId);
}