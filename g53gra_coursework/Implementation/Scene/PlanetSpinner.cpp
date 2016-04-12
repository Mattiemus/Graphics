#include "Implementation/Scene/PlanetSpinner.hpp"
#include "Engine/Core/Engine.hpp"
#include "Engine/Graphics/PrimativeGenerator.hpp"

#define PI 3.14159f

using namespace std;

PlanetSpinner::PlanetSpinner(Material* centerMaterial, Material* planetsMaterial)
    : _centerMaterial(centerMaterial), _center(nullptr), _light(nullptr)
{
    // Create the center column
    vector<Mesh*> centerMeshes;
    Mesh* base = PrimativeGenerator::generateCylinder(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), 16, 2.3f, 5.0f, true);
    Mesh* column = PrimativeGenerator::generateCylinder(Vector3(0.0f, 2.0f, 0.0f), Vector3(1.0f, 5.0f, 1.0f), 16, 0.5f, 0.5f, true);
    Mesh* cap = PrimativeGenerator::generateCylinder(Vector3(0.0f, 4.5f, 0.0f), Vector3(1.0f, 0.3f, 1.0f), 16, 1.5f, 1.0f, true);
    Mesh* sun = PrimativeGenerator::generateSphere(Vector3(0.0f, 5.6f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), 16, 32);
    centerMeshes.push_back(base);
    centerMeshes.push_back(column);
    centerMeshes.push_back(cap);
    centerMeshes.push_back(sun);

    // Invert the normals on the sun
    for (size_t i = 0; i < sun->getVertexCount(); i++) {
        sun->getVertices()[i].normal = sun->getVertices()[i].normal * -1.0f;
    }

    // Combine the meshes
    _center = Mesh::combineMeshes(centerMeshes);

    // Cleanup
    for (Mesh* mesh : centerMeshes) {
        delete mesh;
    }

    // Add some children
    Planet* planetA = new Planet(planetsMaterial, 2.8f, 0.4f, false);
    planetA->getLocalTransform().setTranslation(Vector3(0.0f, 1.6f, 0.0f));
    addChild(planetA);

    Planet* planetB = new Planet(planetsMaterial, 2.0f, 0.6f, true);
    planetB->getLocalTransform().setTranslation(Vector3(0.0f, 2.2f, 0.0f));
    addChild(planetB);

    Planet* planetC = new Planet(planetsMaterial, 1.2f, 0.8f, false);
    planetC->getLocalTransform().setTranslation(Vector3(0.0f, 3.0f, 0.0f));
    addChild(planetC);

    // Add the light for the sun
    _light = new Light();
    _light->setColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    _light->setAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
    _light->setPower(2000000.0f);
    Engine::getInstance().addLight(_light);
}

PlanetSpinner::~PlanetSpinner()
{
    delete _center;
}

void PlanetSpinner::draw(float deltaTime, float totalTime)
{
    _light->setPosition(getWorldTransform().getTranslation() + (Vector3(0.0f, 5.0f, 0.0f) * getWorldTransform().getScale()));

    _centerMaterial->draw(getWorldTransform().getMatrix(), totalTime);
    _center->draw(deltaTime, totalTime);

    SceneObject::draw(deltaTime, totalTime);
}

Planet::Planet(Material* planetMaterial, float armLength, float speed, bool hasChild)
    : _planetMaterial(planetMaterial), _planet(nullptr), _armLength(armLength), _rotationalSpeed(speed)
{
    // Create the planets
    vector<Mesh*> planetMeshes;

    // Create the first arm
    Mesh* armPartA = PrimativeGenerator::generateCylinder(Vector3(0.0f, armLength / 2.0f, 0.0f), Vector3(1.0f, armLength, 1.0f), 16, 0.15f, 0.15f, true);
    Transform armATrans;
    armATrans.setRotation(Quaternion::fromAngleAxis(PI / 2.0f, Vector3(1.0f, 0.0f, 0.0f)));
    armPartA->transformBy(armATrans.getMatrix());
    planetMeshes.push_back(armPartA);

    // Then the connection to the planet
    Mesh* armPartB = PrimativeGenerator::generateCylinder(Vector3(0.0f, 0.625f, 0.0f), Vector3(1.0f, 1.25f, 1.0f), 16, 0.15f, 0.15f, true);
    Transform armBTrans;
    armBTrans.setRotation(Quaternion::fromAngleAxis(PI / 3.0f, Vector3(1.0f, 0.0f, 0.0f)));
    armBTrans.setTranslation(Vector3(0.0f, 0.0f, armLength - 0.07f));
    armPartB->transformBy(armBTrans.getMatrix());
    planetMeshes.push_back(armPartB);

    // And finally the planet
    Mesh* planet = PrimativeGenerator::generateSphere(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.5f, 0.5f, 0.5f), 12, 28);
    Transform planetTrans;
    planetTrans.setTranslation(Vector3(0.0f, 0.8f, armLength + 1.0f));
    planet->transformBy(planetTrans.getMatrix());
    planetMeshes.push_back(planet);

    // Combine the meshes
    _planet = Mesh::combineMeshes(planetMeshes);

    // Cleanup
    for (Mesh* mesh : planetMeshes) {
        delete mesh;
    }

    // Add a child
    if (hasChild) {
        Planet* child = new Planet(planetMaterial, 1.2f, 0.8f, false);
        child->getLocalTransform().setTranslation(Vector3(0.0f, 0.8f, armLength + 1.0f));
        child->getLocalTransform().setScale(Vector3(0.5f, 0.5f, 0.5f));
        addChild(child);
    }
}

Planet::~Planet()
{
    delete _planet;
}

void Planet::draw(float deltaTime, float totalTime)
{
    getLocalTransform().setRotation(Quaternion::fromAngleAxis(totalTime * this->_rotationalSpeed, Vector3(0.0f, 1.0f, 0.0f)));

    _planetMaterial->draw(getWorldTransform().getMatrix(), totalTime);
    _planet->draw(deltaTime, totalTime);

    SceneObject::draw(deltaTime, totalTime);
}