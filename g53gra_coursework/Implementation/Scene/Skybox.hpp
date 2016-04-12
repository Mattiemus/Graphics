#ifndef IMPLEMENTATION_SCENE_SKYBOX_HPP
#define IMPLEMENTATION_SCENE_SKYBOX_HPP

#include "Engine/Scene/SceneObject.hpp"
#include "Engine/Graphics/Material.hpp"
#include "Engine/Graphics/Mesh.hpp"

class Skybox : public SceneObject
{
public:
    Skybox(Material* front, Material* back, Material* top, Material* left, Material* right);
    Skybox(const Skybox &other) = delete;
    virtual ~Skybox();

    virtual void draw(float deltaTime, float totalTime);

    Skybox &operator =(const Skybox &other) = delete;

private:
    Material* _frontMaterial;
    Material* _backMaterial;
    Material* _topMaterial;
    Material* _leftMaterial;
    Material* _rightMaterial;
    Mesh* _front;
    Mesh* _back;
    Mesh* _top;
    Mesh* _left;
    Mesh* _right;
};

#endif