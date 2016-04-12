#include "Implementation/Scene/Bench.hpp"
#include "Engine/Graphics/PrimativeGenerator.hpp"

using namespace std;

Bench::Bench(Material* legsMaterial, Material* seatMaterial)
    : _legsMaterial(legsMaterial), _seatMaterial(seatMaterial), _legs(nullptr), _seat(nullptr)
{
    // Create the legs
    vector<Mesh*> legs;
    Mesh* legA = PrimativeGenerator::generateCylinder(Vector3(0.0f, 0.5f, 1.7f), Vector3(1.0f, 1.0f, 1.0f), 16, 0.8f, 0.8f, false);
    Mesh* legB = PrimativeGenerator::generateCylinder(Vector3(0.0f, 0.5f, -1.7f), Vector3(1.0f, 1.0f, 1.0f), 16, 0.8f, 0.8f, false);
    legs.push_back(legA);
    legs.push_back(legB);

    // Combine into single mesh
    _legs = Mesh::combineMeshes(legs);

    // Clean up
    delete legA;
    delete legB;

    // Create the seat
    _seat = PrimativeGenerator::generateCube(Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.2f, 4.3f));
}

Bench::~Bench()
{
    delete _legs;
    delete _seat;
}

void Bench::draw(float deltaTime, float totalTime)
{
    _legsMaterial->draw(getWorldTransform().getMatrix(), totalTime);
    _legs->draw(deltaTime, totalTime);

    _seatMaterial->draw(getWorldTransform().getMatrix(), totalTime);
    _seat->draw(deltaTime, totalTime);

    SceneObject::draw(deltaTime, totalTime);
}