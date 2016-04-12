#ifndef CORE_GRAPHICS_MESH_HPP
#define CORE_GRAPHICS_MESH_HPP

#include "Engine/Core/Drawable.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vector3.hpp"

#include <vector>

#pragma pack(push, 1)
struct MeshVertexData
{
    MeshVertexData();
    MeshVertexData(const Vector3 &pos, const Vector2 &texCoord);
    MeshVertexData(const Vector3 &pos, const Vector3 &normal, const Vector2 &texCoord);

    Vector2 uv;
    Vector3 position;
    Vector3 normal;
    Vector3 tangent;
    Vector3 bitangent;
};
#pragma pack(pop)

class Mesh
{
    friend class PrimativeGenerator;
    friend class Tree;
    friend class Fire;

public:
    Mesh();
    Mesh(const Mesh &other) = delete;
    virtual ~Mesh();

    static Mesh* fromFile(const char* file);
    static Mesh* fromValues(std::vector<MeshVertexData> &vertices, const std::vector<unsigned int> &indices, bool genNormals, bool genTangents);
    static Mesh* combineMeshes(const std::vector<Mesh*> &meshes);

    const MeshVertexData* getVertices() const
    {
        return _vertexData.data();
    }

    MeshVertexData* getVertices()
    {
        return _vertexData.data();
    }

    const unsigned int* getIndices() const
    {
        return _indices.data();
    }
    
    unsigned int* getIndices()
    {
        return _indices.data();
    }

    size_t getVertexCount() const
    {
        return _vertexData.size();
    }

    size_t getIndexCount() const
    {
        return _indices.size();
    }

    void transformBy(const Matrix4x4 &matrix);
           
    void setVertices(const std::vector<MeshVertexData> &verts);
    void setIndices(const std::vector<unsigned int> &indices);

    void updateVertexBuffer();
    void updateIndexBuffer();

    virtual void draw(float deltaTime, float totalTime);

    Mesh &operator =(const Mesh &other) = delete;

private:
    std::vector<MeshVertexData> _vertexData;
    std::vector<unsigned int> _indices;
    unsigned int _vbo;
    unsigned int _ibo;
    bool _isDoubleSided;
};

#endif