#include "Implementation/Scene/Grass.hpp"
#include "Engine/Graphics/PrimativeGenerator.hpp"
#include "Engine/Math/Quaternion.hpp"

#define PI 3.14159f

using namespace std;

Grass::Grass(Terrain* terrain, Material* bladesMaterial, size_t xCount, size_t yCount, float xMultiplier, float yMultiplier)
    : _material(bladesMaterial), _mesh(nullptr)
{
    auto randFloat = []() { return static_cast<float>(rand()) / static_cast<float>(RAND_MAX); };

    // Create a plane (used to copy vertices)
    Mesh* plane = PrimativeGenerator::generatePlane(Vector3(0.0f, 0.5f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));

    // Create a bunch of grass
    vector<MeshVertexData> vertices; vertices.reserve(plane->getVertexCount() * xCount * yCount);
    vector<unsigned int> indices; indices.reserve(plane->getIndexCount() * xCount * yCount);
    unsigned int indexOffset = 0;
    for (size_t x = 0; x < xCount; x++) {
        for (size_t y = 0; y < yCount; y++) {
            // Get the height 
            float xNormed = static_cast<float>(x) / static_cast<float>(xCount);
            float yNormed = static_cast<float>(y) / static_cast<float>(yCount);
            float height = terrain->getHeight(xNormed, yNormed);

            // Do not create grass on high planes
            if (height < 0.5f) {
                // Create a random transform
                Transform transform;
                transform.setRotation(Quaternion::fromAngleAxis((PI * 2.0f) * randFloat(), Vector3(0.0f, 1.0f, 0.0f)));
                transform.setTranslation(Vector3(static_cast<float>(x)* xMultiplier, height, static_cast<float>(y)* yMultiplier));
                transform.setScale(Vector3(1.0f, 0.3f, 1.0f) + (Vector3(0.0f, 1.0f, 0.0f) * randFloat()));

                // Copy the vertices (translate them too!)
                for (size_t i = 0; i < plane->getVertexCount(); i++) {
                    MeshVertexData vertex = plane->getVertices()[i];
                    vertex.position.transform(transform.getMatrix());
                    vertices.push_back(vertex);
                }

                // Copy the offset indices
                for (size_t i = 0; i < plane->getIndexCount(); i++) {
                    indices.push_back(plane->getIndices()[i] + indexOffset);
                }
                indexOffset += plane->getVertexCount();
            }
        }
    }

    // Combine the meshes into one
    _mesh = Mesh::fromValues(vertices, indices, true, true);

    // Clean up
    delete plane;
}

Grass::~Grass()
{
    delete _mesh;
}

void Grass::draw(float deltaTime, float totalTime)
{
    // Draw the branch
    _material->draw(getWorldTransform().getMatrix(), totalTime);
    _mesh->draw(deltaTime, totalTime);

    // Draw all children
    SceneObject::draw(deltaTime, totalTime);
}