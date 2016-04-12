#include "Implementation/Scene/FirePit.hpp"
#include "Implementation/Scene/Fire.hpp"
#include "Engine/Graphics/PrimativeGenerator.hpp"

FirePit::FirePit(Material* bottomMaterial, Material* topMaterial, Material* fireMaterial, Material* logsMaterial)
    : _bottomMaterial(bottomMaterial), _topMaterial(topMaterial), _bottomMesh(nullptr), _topMesh(nullptr)
{
    _bottomMesh = PrimativeGenerator::generateCylinder(Vector3(0.0f, 0.0f, 0.0f), Vector3(2.5f, 2.5f, 2.5f), 18, 1.0f, 1.0f, true);
    _topMesh = PrimativeGenerator::generateCylinder(Vector3(0.0f, 1.25f, 0.0f), Vector3(2.5f, 0.1f, 2.5f), 18, 1.1f, 1.1f, true);

    Fire* fire = new Fire(fireMaterial, logsMaterial);
    fire->getLocalTransform().setTranslation(Vector3(0.0f, 1.25f, 0.0f));
    addChild(fire);
}

FirePit::~FirePit()
{
    delete _bottomMesh;
    delete _topMesh;
}

void FirePit::draw(float deltaTime, float totalTime)
{
    _topMaterial->draw(getWorldTransform().getMatrix(), totalTime);
    _topMesh->draw(deltaTime, totalTime);

    _bottomMaterial->draw(getWorldTransform().getMatrix(), totalTime);
    _bottomMesh->draw(deltaTime, totalTime);

    SceneObject::draw(deltaTime, totalTime);
}