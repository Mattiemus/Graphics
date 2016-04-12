#ifndef IMPLEMENTATION_SCENE_TREE_HPP
#define IMPLEMENTATION_SCENE_TREE_HPP

#include "Engine/Scene/SceneObject.hpp"
#include "Engine/Graphics/Material.hpp"
#include "Engine/Graphics/Mesh.hpp"

class Tree : public SceneObject
{
public:
    Tree(size_t treeSeed, Material* barkMaterial, Material* leavesMaterial);
    Tree(const Tree &other) = delete;
    virtual ~Tree();

    static Tree* cloneTree(Tree* tree);

    virtual void draw(float deltaTime, float totalTime);

    Tree &operator =(const Tree &other) = delete;

private:
    Tree(Mesh* branch, Mesh* leaves, Material* barkMaterial, Material* leavesMaterial);

    bool _ownsMesh;
    Mesh* _branchMesh;
    Mesh* _leavesMesh;
    Material* _barkMaterial;
    Material* _leavesMaterial;
};

class TreeBranch : public SceneObject
{
public:
    TreeBranch(bool hasLeaves, size_t levels, size_t leavesCount, size_t initialSubLevels, size_t subLevels,
        float startSize, Material* barkMaterial, Material* leavesMaterial);
    TreeBranch(const TreeBranch &other) = delete;
    virtual ~TreeBranch();

    void addMeshes(std::vector<std::pair<Mesh*, Matrix4x4>> &branches, std::vector<std::pair<Mesh*, Matrix4x4>> &leaves);

    virtual void draw(float deltaTime, float totalTime);

    TreeBranch &operator =(const TreeBranch &other) = delete;

private:
    Mesh* _branchMesh;
    Mesh* _leavesMesh;
    Material* _barkMaterial;
    Material* _leavesMaterial;
};

#endif