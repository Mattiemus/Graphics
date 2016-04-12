#ifndef IMPLEMENTATION_SCENE_TERRAIN_HPP
#define IMPLEMENTATION_SCENE_TERRAIN_HPP

#include "Engine/Scene/SceneObject.hpp"
#include "Engine/Graphics/Material.hpp"
#include "Engine/Graphics/Mesh.hpp"

class Terrain : public SceneObject
{
public:
    Terrain(const char* heightmapFile, Material* material);
    Terrain(const Terrain &other) = delete;
    virtual ~Terrain();
       
    float getHeight(float normedX, float normedY);

    virtual void draw(float deltaTime, float totalTime);

    Terrain &operator =(const Terrain &other) = delete;

private:
    float* _heightmap;
    size_t _heightmapWidth;
    size_t _heightmapHeight;
    Material* _material;
    Mesh* _mesh;
};

#endif