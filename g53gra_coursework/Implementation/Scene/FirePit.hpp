#ifndef IMPLEMENTATION_SCENE_FIREPIT_HPP
#define IMPLEMENTATION_SCENE_FIREPIT_HPP

#include "Implementation/Scene/Terrain.hpp"
#include "Engine/Scene/SceneObject.hpp"
#include "Engine/Graphics/Material.hpp"
#include "Engine/Graphics/Mesh.hpp"

class FirePit : public SceneObject
{
public:
    FirePit(Material* bottomMaterial, Material* topMaterial, Material* fireMaterial, Material* logsMaterial);
    FirePit(const FirePit &other) = delete;
    virtual ~FirePit();

    virtual void draw(float deltaTime, float totalTime);

    FirePit &operator =(const FirePit &other) = delete;

private:
    Material* _bottomMaterial;
    Material* _topMaterial;
    Mesh* _bottomMesh;
    Mesh* _topMesh;
};

#endif