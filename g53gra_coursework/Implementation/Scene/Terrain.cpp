#include "Implementation/Scene/Terrain.hpp"
#include "Engine/Graphics/Texture.hpp"

#include <limits>

using namespace std;

Terrain::Terrain(const char* heightmapFile, Material* material)
    : _heightmap(nullptr), _material(material), _mesh(nullptr)
{
    // Load the heights from the texture
    _heightmap = Texture::heightsFromFile(heightmapFile, _heightmapWidth, _heightmapHeight);
    
    // Create buffers for the vertex data
    vector<MeshVertexData> vertices;
    vector<unsigned int> indices;
    
    // Add the vertex points
    for (size_t x = 0; x < _heightmapWidth; x++) {
        for (size_t y = 0; y < _heightmapHeight; y++) {
            // Make sure that the generated terrain will take up a (1.0 x 1.0 x 1.0) cube
            // so that it scales correctly
            float relX = (static_cast<float>(x) / static_cast<float>(_heightmapWidth));
            float relY = (static_cast<float>(y) / static_cast<float>(_heightmapHeight));

            // Get the height
            float height = _heightmap[y * _heightmapHeight + x];
            
            // Add the vertex
            vertices.push_back(MeshVertexData(Vector3(relX - 0.5f, height - 0.5f, relY - 0.5f),
                Vector2(relX, relY)));
        }
    }
    
    // Now compute the triangles
    for (size_t x = 0; x < _heightmapWidth - (_heightmapWidth % 3); x++) {
        for (size_t y = 0; y < _heightmapHeight - (_heightmapHeight % 3); y++) {
            // Triangle 1 indices
            unsigned int i1 = y * _heightmapHeight + x;
            unsigned int i2 = y * _heightmapHeight + (x + 1);
            unsigned int i3 = (y + 1) * _heightmapHeight + x;

            // Triangle 2 indices
            unsigned int i4 = y * _heightmapHeight + (x + 1);
            unsigned int i5 = (y + 1) * _heightmapHeight + (x + 1);
            unsigned int i6 = (y + 1) * _heightmapHeight + x;

            // Add both triangles
            indices.push_back(i1);
            indices.push_back(i2);
            indices.push_back(i3);
            indices.push_back(i4);
            indices.push_back(i5);
            indices.push_back(i6);
        }
    }
    
    // Create the mesh
    _mesh = Mesh::fromValues(vertices, indices, true, true);
}

Terrain::~Terrain()
{
    delete _heightmap;
}

float Terrain::getHeight(float normedX, float normedY)
{
    size_t x = static_cast<size_t>(floor(normedX * _heightmapWidth));
    size_t y = static_cast<size_t>(floor(normedY * _heightmapHeight));
    return _heightmap[y * _heightmapHeight + x];
}

void Terrain::draw(float deltaTime, float totalTime)
{
    // Set all material parameters
    _material->draw(getWorldTransform().getMatrix(), totalTime);
    
    // Draw the shader
    _mesh->draw(deltaTime, totalTime);

    // Draw all children
    SceneObject::draw(deltaTime, totalTime);
}