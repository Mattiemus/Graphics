#include "Engine/Graphics/PrimativeGenerator.hpp"
#include "Engine/Math/Vector2.hpp"

#include <algorithm>
#include <vector>

#define PI 3.141592654f

using namespace std;

PrimativeGenerator::PrimativeGenerator()
{
}

PrimativeGenerator::~PrimativeGenerator()
{
}

Mesh* PrimativeGenerator::generatePlane(const Vector3 &offset, const Vector3 &scale)
{
    // Buffers for the parts of the plane
    vector<MeshVertexData> vertices;
    vector<unsigned int> indices;
    
    // Generate vertices
    vertices.push_back(MeshVertexData(offset + Vector3(-0.5f, -0.5f, 0.0f) * scale,
        Vector2(1.0f, 1.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(0.5f, 0.5f, 0.0f) * scale,
        Vector2(0.0f, 0.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(0.5f, -0.5f, 0.0f) * scale,
        Vector2(0.0f, 1.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(-0.5f, 0.5f, 0.0f) * scale,
        Vector2(1.0f, 0.0f)));

    // Add the indices
    indices.push_back(0); indices.push_back(1); indices.push_back(2);
    indices.push_back(0); indices.push_back(3); indices.push_back(1);

    // Return the generated mesh, using the mesh class to generate the normals
    Mesh* plane = Mesh::fromValues(vertices, indices, true, true);
    plane->_isDoubleSided = true;
    return plane;
}

Mesh* PrimativeGenerator::generateCube(const Vector3 &offset, const Vector3 &scale)
{
    // Buffers for the parts of the cube
    vector<MeshVertexData> vertices;
    vector<unsigned int> indices;

    // Generate vertices
    vertices.push_back(MeshVertexData(offset + Vector3(-0.5f, -0.5f, -0.5f) * scale, 
        Vector2(1.0f, 1.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(0.5f, 0.5f, -0.5f) * scale, 
        Vector2(0.0f, 0.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(0.5f, -0.5f, -0.5f) * scale, 
        Vector2(0.0f, 1.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(-0.5f, 0.5f, -0.5f) * scale, 
        Vector2(1.0f, 0.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(-0.5f, -0.5f, -0.5f) * scale, 
        Vector2(0.0f, 1.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(-0.5f, 0.5f, 0.5f) * scale, 
        Vector2(1.0f, 0.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(-0.5f, 0.5f, -0.5f) * scale, 
        Vector2(0.0f, 0.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(-0.5f, -0.5f, 0.5f) * scale, 
        Vector2(1.0f, 1.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(-0.5f, 0.5f, -0.5f) * scale, 
        Vector2(0.0f, 0.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(0.5f, 0.5f, 0.5f) * scale, 
        Vector2(1.0f, 1.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(0.5f, 0.5f, -0.5f) * scale, 
        Vector2(1.0f, 0.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(-0.5f, 0.5f, 0.5f) * scale, 
        Vector2(0.0f, 1.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(0.5f, -0.5f, -0.5f) * scale, 
        Vector2(1.0f, 1.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(0.5f, 0.5f, -0.5f) * scale, 
        Vector2(1.0f, 0.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(0.5f, 0.5f, 0.5f) * scale, 
        Vector2(0.0f, 0.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(0.5f, -0.5f, 0.5f) * scale, 
        Vector2(0.0f, 1.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(-0.5f, -0.5f, -0.5f) * scale, 
        Vector2(0.0f, 1.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(0.5f, -0.5f, -0.5f) * scale, 
        Vector2(1.0f, 1.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(0.5f, -0.5f, 0.5f) * scale, 
        Vector2(1.0f, 0.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(-0.5f, -0.5f, 0.5f) * scale, 
        Vector2(0.0f, 0.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(-0.5f, -0.5f, 0.5f) * scale, 
        Vector2(0.0f, 1.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(0.5f, -0.5f, 0.5f) * scale, 
        Vector2(1.0f, 1.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(0.5f, 0.5f, 0.5f) * scale, 
        Vector2(1.0f, 0.0f)));
    vertices.push_back(MeshVertexData(offset + Vector3(-0.5f, 0.5f, 0.5f) * scale, 
        Vector2(0.0f, 0.0f)));

    // Add the indices
    indices.push_back(0); indices.push_back(1); indices.push_back(2);
    indices.push_back(0); indices.push_back(3); indices.push_back(1);
    indices.push_back(4); indices.push_back(5); indices.push_back(6);
    indices.push_back(4); indices.push_back(7); indices.push_back(5);
    indices.push_back(8); indices.push_back(9); indices.push_back(10);
    indices.push_back(8); indices.push_back(11); indices.push_back(9);
    indices.push_back(12); indices.push_back(13); indices.push_back(14);
    indices.push_back(12); indices.push_back(14); indices.push_back(15);
    indices.push_back(16); indices.push_back(17); indices.push_back(18);
    indices.push_back(16); indices.push_back(18); indices.push_back(19);
    indices.push_back(20); indices.push_back(21); indices.push_back(22);
    indices.push_back(20); indices.push_back(22); indices.push_back(23);

    // Return the generated mesh, using the mesh class to generate the normals
    return Mesh::fromValues(vertices, indices, true, true);
}

Mesh* PrimativeGenerator::generateCylinder(const Vector3 &offset, const Vector3 &scale, unsigned int radialSegments, float topRadius, float bottomRadius, bool genCaps)
{
    // Make sure we have the correct segment count
    radialSegments = max(radialSegments, 3u);

    // Buffers for the parts of the cylinder
    vector<MeshVertexData> vertices;
    vector<unsigned int> indices;

    // Create the body of the cylinder
    for (size_t i = 0; i < radialSegments; i++) {
        // Compute the x and y positions;
        float theta = (2.0f * PI * i) / (radialSegments - 1);
        float x = sin(theta);
        float y = cos(theta);

        // Create the vertices
        vertices.push_back(MeshVertexData(offset + Vector3(x * topRadius / 2.0f, 0.5f, y * topRadius / 2.0f) * scale,
            Vector3(x, 0.0f, y),
            Vector2(static_cast<float>(i) / static_cast<float>(radialSegments - 1) * 3.0f, 0.0f)));
        vertices.push_back(MeshVertexData(offset + Vector3(x * bottomRadius / 2.0f, -0.5f, y * bottomRadius / 2.0f) * scale,
            Vector3(x, 0.0f, y),
            Vector2(static_cast<float>(i) / static_cast<float>(radialSegments - 1) * 3.0f, 1.0f)));
    }

    // Add the indices
    for (size_t i = 0; i < radialSegments - 1; i++) {
        indices.push_back((i * 2) + 0);
        indices.push_back((i * 2) + 1);
        indices.push_back(((i + 1) * 2) + 0);

        indices.push_back(((i + 1) * 2) + 0);
        indices.push_back((i * 2) + 1);
        indices.push_back(((i + 1) * 2) + 1);
    }

    // Generate caps if needed
    if (genCaps) {
        // Offset for the caps
        size_t capsOffset = vertices.size();

        // Centers for top and bottom
        vertices.push_back(MeshVertexData(offset + Vector3(0.0f, 0.5f, 0.0f) * scale,
            Vector3(0.0f, 1.0f, 0.0f),
            Vector2(0.5f, 0.5f)));
        vertices.push_back(MeshVertexData(offset + Vector3(0.0f, -0.5f, 0.0f) * scale,
            Vector3(0.0f, -1.0f, 0.0f),
            Vector2(0.5f, 0.5f)));

        // Create the body of the cylinder
        for (size_t i = 0; i < radialSegments; i++) {
            // Compute the x and y positions;
            float theta = (2.0f * PI * i) / (radialSegments - 1);
            float x = sin(theta);
            float y = cos(theta);

            // Create the vertices
            vertices.push_back(MeshVertexData(offset + Vector3(x * topRadius / 2.0f, 0.5f, y * topRadius / 2.0f) * scale,
                Vector3(0.0f, 1.0f, 0.0f),
                Vector2(x * 0.5f + 0.5f, y * 0.5f + 0.5f)));
            vertices.push_back(MeshVertexData(offset + Vector3(x * bottomRadius / 2.0f, -0.5f, y * bottomRadius / 2.0f) * scale,
                Vector3(0.0f, -1.0f, 0.0f),
                Vector2(x * 0.5f + 0.5f, y * 0.5f + 0.5f)));
        }

        // Add the indices
        for (size_t i = 0; i < radialSegments - 1; i++) {
            indices.push_back(capsOffset + (0));
            indices.push_back(capsOffset + (2 + (i * 2) + 0));
            indices.push_back(capsOffset + (2 + ((i + 1) * 2) + 0));

            indices.push_back(capsOffset + (2 + ((i + 1) * 2) + 1));
            indices.push_back(capsOffset + (2 + (i * 2) + 1));
            indices.push_back(capsOffset + (1));
        }
    }

    // Return the generated mesh
    return Mesh::fromValues(vertices, indices, false, true);
}

Mesh* PrimativeGenerator::generateSphere(const Vector3 &offset, const Vector3 &scale, unsigned int heightSegments, unsigned int widthSegments)
{   
    // Create the vertices
    vector<MeshVertexData> vertices;
    for (size_t j = 1; j < heightSegments - 1; j++) {
        for (size_t i = 0; i < widthSegments; i++) {
            // Compute the vertex position
            float theta = static_cast<float>(j) / (heightSegments - 1) * PI;
            float phi = static_cast<float>(i) / (widthSegments - 1) * PI * 2.0f;
            Vector3 pos(cos(phi) * sin(theta),
                sin(phi) * sin(theta),
                cos(theta));

            float texTheta = acos(pos.y) / PI;
            float texPhi = (atan2(pos.x, pos.z) + PI) / (PI * 2.0f);

            // Make the vertex
            vertices.push_back(MeshVertexData(offset + (pos * scale), 
                pos,
                Vector2(texTheta, texPhi)));
        }
    }
    vertices.push_back(MeshVertexData(offset + (Vector3(0.0f, 1.0f, 0.0f) * scale),
        Vector3(0.0f, 1.0f, 0.0f),
        Vector2(0.0f, 0.0f)));
    vertices.push_back(MeshVertexData(offset + (Vector3(0.0f, -1.0f, 0.0f) * scale),
        Vector3(0.0f, -1.0f, 0.0f),
        Vector2(0.0f, 0.0f)));

    // Now generate the indices
    vector<unsigned int> indices;
    for (size_t j = 0; j < heightSegments - 3; j++) {
        for (size_t i = 0; i < widthSegments - 1; i++) {
            indices.push_back(j * widthSegments + i);
            indices.push_back((j + 1) * widthSegments + i + 1);
            indices.push_back(j * widthSegments + i + 1);

            indices.push_back(j * widthSegments + i);
            indices.push_back((j + 1) * widthSegments + i);
            indices.push_back((j + 1) * widthSegments + i + 1);
        }
    }
    for (size_t i = 0; i < widthSegments - 1; i++) {
        indices.push_back((heightSegments - 2) * widthSegments);
        indices.push_back(i);
        indices.push_back(i + 1);

        indices.push_back((heightSegments - 2) * widthSegments + 1);
        indices.push_back((heightSegments - 3) * widthSegments + i + 1);
        indices.push_back((heightSegments - 3) * widthSegments + i);
    }

    // Return the generated mesh
    return Mesh::fromValues(vertices, indices, false, true);
}