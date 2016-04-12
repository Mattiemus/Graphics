#ifndef IMPLEMENTATION_SCENE_FIRE_HPP
#define IMPLEMENTATION_SCENE_FIRE_HPP

#include "Implementation/Scene/Terrain.hpp"
#include "Engine/Scene/SceneObject.hpp"
#include "Engine/Graphics/Material.hpp"
#include "Engine/Graphics/Mesh.hpp"

class Fire : public SceneObject
{
public:
    Fire(Material* fireMaterial, Material* logsMaterial);
    Fire(const Fire &other) = delete;
    virtual ~Fire();

    virtual void draw(float deltaTime, float totalTime);

    Fire &operator =(const Fire &other) = delete;

private:
    Material* _fireMaterial;
    Material* _logsMaterial;
    Mesh* _fireA;
    Mesh* _fireB;
    Mesh* _logs;
};

#endif