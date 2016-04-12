#ifndef IMPLEMENTATION_SCENE_GRASS_HPP
#define IMPLEMENTATION_SCENE_GRASS_HPP

#include "Implementation/Scene/Terrain.hpp"
#include "Engine/Scene/SceneObject.hpp"
#include "Engine/Graphics/Material.hpp"
#include "Engine/Graphics/Mesh.hpp"

class Grass : public SceneObject
{
public:
    Grass(Terrain* terrain, Material* bladesMaterial, size_t xCount, size_t yCount, float xMultiplier, float yMultiplier);
    Grass(const Grass &other) = delete;
    virtual ~Grass();

    virtual void draw(float deltaTime, float totalTime);

    Grass &operator =(const Grass &other) = delete;

private:
    Material* _material;
    Mesh* _mesh;
};

#endif