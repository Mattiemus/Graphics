#include "Engine/Graphics/Mesh.hpp"
#include "Engine/Loaders/tiny_obj_loader.h"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Core/GL.hpp"

#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace tinyobj;

MeshVertexData::MeshVertexData()
    : uv(0.0f, 0.0f), position(0.0f, 0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f), tangent(0.0f, 0.0f, 0.0f), bitangent(0.0f, 0.0f, 0.0f)
{
}

MeshVertexData::MeshVertexData(const Vector3 &pos, const Vector2 &texCoord)
    : uv(texCoord), position(pos), normal(0.0f, 0.0f, 0.0f), tangent(0.0f, 0.0f, 0.0f), bitangent(0.0f, 0.0f, 0.0f)
{
}

MeshVertexData::MeshVertexData(const Vector3 &pos, const Vector3 &normal, const Vector2 &texCoord)
    : uv(texCoord), position(pos), normal(normal), tangent(0.0f, 0.0f, 0.0f), bitangent(0.0f, 0.0f, 0.0f)
{
}

Mesh::Mesh()
    : _isDoubleSided(false)
{
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glGenBuffers(1, &_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
}

Mesh::~Mesh()
{
}

Mesh* Mesh::fromFile(const char* filePath)
{
    // Load the file
    vector<shape_t> shapes;
    vector<material_t> materials;
    LoadObj(shapes, materials, filePath);

    // Combine all the shapes into one
    vector<MeshVertexData> vertices;
    vector<unsigned int> indices;
    unsigned int indiciesPos = 0;
    for (const shape_t &shape : shapes) {
        // Genereate vertex data
        for (size_t i = 0; i < shape.mesh.positions.size() / 3; i++) {
            MeshVertexData data;
            data.position = Vector3(shape.mesh.positions[(i * 3) + 0], shape.mesh.positions[(i * 3) + 1], shape.mesh.positions[(i * 3) + 2]);
            data.normal = Vector3(shape.mesh.normals[(i * 3) + 0], shape.mesh.normals[(i * 3) + 1], shape.mesh.normals[(i * 3) + 2]);
            data.uv = Vector2(shape.mesh.texcoords[(i * 2) + 0], shape.mesh.texcoords[(i * 2) + 1]);
            vertices.push_back(data);
        }
        
        // Offset the indicies by the current index value
        for (auto it = shape.mesh.indices.begin(); it != shape.mesh.indices.end(); ++it) {
            indices.push_back(indiciesPos + *it);
        }
        indiciesPos += shape.mesh.positions.size() / 3;
    }

    // Create and return the mesh
    return fromValues(vertices, indices, false, true);
}

Mesh* Mesh::fromValues(std::vector<MeshVertexData> &vertices, const std::vector<unsigned int> &indices, bool genNormals, bool genTangents)
{
    // Genereate surface normals (if needed)
    if (genNormals) {
        // Loop over all the indicies 3 at a time (1 triangle)
        for (size_t i = 0; i < indices.size(); i += 3) {
            // Triangle 1 indices
            unsigned int i1 = indices[i + 0];
            unsigned int i2 = indices[i + 1];
            unsigned int i3 = indices[i + 2];

            // Get the positions
            Vector3 p1(vertices[i1].position);
            Vector3 p2(vertices[i2].position);
            Vector3 p3(vertices[i3].position);

            // Compute the normal
            Vector3 norm = Vector3::cross(p2 - p1, p3 - p1);
            if (norm.length() < numeric_limits<float>::epsilon()) {
                norm = Vector3(0.0f, 1.0f, 0.0f);
            }
            norm.normalize();

            // Add the normals to the buffers
            vertices[i1].normal = norm;
            vertices[i2].normal = norm;
            vertices[i3].normal = norm;
        }
    }

    // Genereate tangents (if needed)
    if (genTangents) {
        // Compute tangents
        for (size_t i = 0; i < indices.size(); i += 3) {
            // Get the indicies we need
            int i1 = indices[i + 0];
            int i2 = indices[i + 1];
            int i3 = indices[i + 2];

            // Verticies
            Vector3 v0(vertices[i1].position);
            Vector3 v1(vertices[i2].position);
            Vector3 v2(vertices[i3].position);

            // Texture coordinates
            Vector2 uv0(vertices[i1].uv);
            Vector2 uv1(vertices[i2].uv);
            Vector2 uv2(vertices[i3].uv);

            // Positional delta
            Vector3 deltaPos1 = v1 - v0;
            Vector3 deltaPos2 = v2 - v0;

            // Texture coordinate delta
            Vector2 deltaUV1 = uv1 - uv0;
            Vector2 deltaUV2 = uv2 - uv0;

            // Compute
            float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
            Vector3 tangent((deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r);
            Vector3 bitangent((deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r);

            // Add the tangent vectors
            vertices[i1].tangent = vertices[i1].tangent + tangent;
            vertices[i2].tangent = vertices[i2].tangent + tangent;
            vertices[i3].tangent = vertices[i3].tangent + tangent;

            // Add the bitangent vectors
            vertices[i1].bitangent = vertices[i1].bitangent + bitangent;
            vertices[i2].bitangent = vertices[i2].bitangent + bitangent;
            vertices[i3].bitangent = vertices[i3].bitangent + bitangent;
        }

        // Normalise all the computed tangents
        for (size_t i = 0; i < vertices.size(); i++) {
            // Normalise tangent
            vertices[i].tangent.normalize();
            vertices[i].bitangent.normalize();
        }
    }

    // Create the mesh
    Mesh* loadedMesh = new Mesh();
    loadedMesh->setVertices(vertices);
    loadedMesh->setIndices(indices);
    loadedMesh->updateIndexBuffer();
    loadedMesh->updateVertexBuffer();
    return loadedMesh;
}

Mesh* Mesh::combineMeshes(const std::vector<Mesh*> &meshes)
{
    // Precompute the resulting size
    size_t vertexDataSize = 0;
    size_t indicesDataSize = 0;
    for (Mesh* mesh : meshes) {
        vertexDataSize += mesh->getVertexCount();
        indicesDataSize += mesh->getIndexCount();
    }

    // Combine all the meshes into one buffer first
    vector<MeshVertexData> vertexData; vertexData.reserve(vertexDataSize);
    vector<unsigned int> indices; indices.reserve(indicesDataSize);
    unsigned int indexOffset = 0;

    // Combine the meshes
    for (Mesh* mesh : meshes) {
        // Add the vertex data
        vertexData.insert(vertexData.end(), mesh->getVertices(), mesh->getVertices() + mesh->getVertexCount());
        
        // Add the indicies, taking the offset into account
        for (size_t i = 0; i < mesh->getIndexCount(); i++) {
            unsigned int index = mesh->getIndices()[i];
            index += indexOffset;
            indices.push_back(index);
        }
        indexOffset += mesh->getVertexCount();
    }

    // Return the computed mesh
    Mesh* loadedMesh = new Mesh();
    loadedMesh->setVertices(vertexData);
    loadedMesh->setIndices(indices);
    loadedMesh->updateIndexBuffer();
    loadedMesh->updateVertexBuffer();
    return loadedMesh;
}

void Mesh::transformBy(const Matrix4x4 &matrix)
{
    for (size_t i = 0; i < _vertexData.size(); i++) {
        _vertexData[i].position.transform(matrix);
    }
}

void Mesh::setVertices(const std::vector<MeshVertexData> &verts)
{
    _vertexData.clear();
    _vertexData.reserve(verts.size());
    _vertexData.insert(_vertexData.end(), verts.begin(), verts.end());
}

void Mesh::setIndices(const std::vector<unsigned int> &indices)
{
    _indices.clear();
    _indices.reserve(indices.size());
    _indices.insert(_indices.end(), indices.begin(), indices.end());
}

void Mesh::updateVertexBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertexData.size() * sizeof(MeshVertexData), _vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::updateIndexBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);
}

void Mesh::draw(float deltaTime, float totalTime)
{  
    // Enable double sided
    if (_isDoubleSided) {
        glDisable(GL_CULL_FACE);
    }

    // Bind the buffers
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

    // Texture coordinates
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertexData), 
        reinterpret_cast<const char*>(offsetof(MeshVertexData, uv)));
    glEnableVertexAttribArray(0);

    // Vertices
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertexData), 
        reinterpret_cast<const char*>(offsetof(MeshVertexData, position)));
    glEnableVertexAttribArray(1);

    // Normals
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertexData), 
        reinterpret_cast<const char*>(offsetof(MeshVertexData, normal)));
    glEnableVertexAttribArray(2);

    // Tangents
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertexData),
        reinterpret_cast<const char*>(offsetof(MeshVertexData, tangent)));
    glEnableVertexAttribArray(3);

    // Bitangents
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertexData), 
        reinterpret_cast<const char*>(offsetof(MeshVertexData, bitangent)));
    glEnableVertexAttribArray(4);
    
    // Draw
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);

    // Disable double sided
    if (_isDoubleSided) {
        glEnable(GL_CULL_FACE);
    }
}
