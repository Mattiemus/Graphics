#include "Implementation/Scene/Tree.hpp"
#include "Engine/Graphics/PrimativeGenerator.hpp"

#define PI 3.14159f

using namespace std;

Tree::Tree(size_t treeSeed, Material* barkMaterial, Material* leavesMaterial)
    : _ownsMesh(true), _branchMesh(nullptr), _leavesMesh(nullptr), _barkMaterial(barkMaterial), _leavesMaterial(leavesMaterial)
{
    // Set the random seed for this tree
    srand(treeSeed);
    
    // Create the trunk
    TreeBranch* root = new TreeBranch(false, 8, 13, 4, 4, 1.8f, barkMaterial, leavesMaterial);
    addChild(root);

    // Combine the tree into one mesh (optimisation)
    vector<pair<Mesh*, Matrix4x4>> branches;
    vector<pair<Mesh*, Matrix4x4>> leaves;
    for (SceneObject* sceneChild : getChildren()) {
        TreeBranch* branchChild = reinterpret_cast<TreeBranch*>(sceneChild);
        branchChild->addMeshes(branches, leaves);
    }
    
    // Translate the branches and leaves
    vector<Mesh*> transformedBranches;
    vector<Mesh*> transformedLeaves;
    for (pair<Mesh*, Matrix4x4> &branch : branches) {
        branch.first->transformBy(branch.second);
        transformedBranches.push_back(branch.first);
    }
    for (pair<Mesh*, Matrix4x4> &leaf : leaves) {
        leaf.first->transformBy(leaf.second);
        transformedLeaves.push_back(leaf.first);
    }

    // Combine
    _branchMesh = Mesh::combineMeshes(transformedBranches);
    _leavesMesh = Mesh::combineMeshes(transformedLeaves);

    // Cleanup
    for (SceneObject* child : _children) {
        delete child;
    }
    _children.clear();
}

Tree::Tree(Mesh* branch, Mesh* leaves, Material* barkMaterial, Material* leavesMaterial)
    : _branchMesh(branch), _leavesMesh(leaves), _barkMaterial(barkMaterial), _leavesMaterial(leavesMaterial)
{
}

Tree::~Tree()
{
    if (_ownsMesh) {
        delete _branchMesh;
        delete _leavesMesh;
    }
}

Tree* Tree::cloneTree(Tree* tree)
{
    return new Tree(tree->_branchMesh, tree->_leavesMesh, tree->_barkMaterial, tree->_leavesMaterial);
}

void Tree::draw(float deltaTime, float totalTime)
{
    // Draw the branch
    _barkMaterial->draw(getWorldTransform().getMatrix(), totalTime);
    _branchMesh->draw(deltaTime, totalTime);

    // Draw the leaves, if we have them
    if (_leavesMesh != nullptr) {
        _leavesMaterial->draw(getWorldTransform().getMatrix(), totalTime);
        _leavesMesh->draw(deltaTime, totalTime);
    }

    // Draw all children
    SceneObject::draw(deltaTime, totalTime);
}

TreeBranch::TreeBranch(bool hasLeaves, size_t levels, size_t leavesCount, size_t initialSubLevels, size_t subLevels, 
    float startLevel, Material* barkMaterial, Material* leavesMaterial)
    : _branchMesh(nullptr), _leavesMesh(nullptr), _barkMaterial(barkMaterial), _leavesMaterial(leavesMaterial)
{
    // Generate random float, and a vector3 from thoes random numbers
    auto randFloat = []() { return static_cast<float>(rand()) / static_cast<float>(RAND_MAX); };
    auto randomVector3 = [&randFloat]() { return Vector3(randFloat(), 0.0f, randFloat()); };

    // Generate the branch from a stack of cylinders
    vector<Mesh*> branchMeshes;
    vector<Vector3> levelOffsets;
    Vector3 levelOffset;
    
    
    for (size_t i = 0; i < levels; i++) {
        // Compute a new level offset and sum
        levelOffsets.push_back(levelOffset);
        Vector3 previousLevelOffset = levelOffset;
        if (hasLeaves) {
            levelOffset = randomVector3() / 1.5f;
        } else {
            levelOffset = randomVector3() / 2.0f;
        }

        // Create the branch level
        float topRadius = startLevel * (1.0f - (static_cast<float>(i + 1) / static_cast<float>(levels)));
        float bottomRadius = startLevel * (1.0f - (static_cast<float>(i) / static_cast<float>(levels)));
        Mesh* newLevel = newLevel = PrimativeGenerator::generateCylinder(Vector3(0.0f, 0.5f + (1.0f * static_cast<float>(i)), 0.0f),
            Vector3(0.5f, 1.0f, 0.5f), 16, topRadius, bottomRadius, false);
        
        // Offset the level by random values, to make it look jagged (like a tree!)
        for (size_t j = 0; j < newLevel->getVertexCount(); j++) {
            float yCoord = newLevel->getVertices()[j].position.y;
            if (yCoord == static_cast<float>(i)) {
                // Bottom part of cylinder
                newLevel->getVertices()[j].position = newLevel->getVertices()[j].position + previousLevelOffset;
            } else {
                // Top part
                newLevel->getVertices()[j].position = newLevel->getVertices()[j].position + levelOffset;
            }
        }

        // Add the branch
        branchMeshes.push_back(newLevel);
    }

    // Combine the meshes (this is an optimisation step, to reduce draw call count)
    _branchMesh = Mesh::combineMeshes(branchMeshes);

    // Clean up
    for (Mesh* mesh : branchMeshes) {
        delete mesh;
    }

    // Genererate leaves
    if (hasLeaves) {
        // Genereate some leaves
        vector<Mesh*> leavesMeshes;
        for (size_t i = 0; i < leavesCount; i++) {
            // Genereate the leaves for a specific level
            float level = (static_cast<float>(levels) * 0.75f * randFloat()) + (static_cast<float>(levels) * 0.25f);
            size_t levelIndex = static_cast<size_t>(floor(level));
            Mesh* leaves = PrimativeGenerator::generatePlane(Vector3(0.0f, -0.5f, -0.1f * (1.0f / level)), 
                Vector3(1.5f, 1.0f, 1.5f));

            // Create a transformation
            Transform leavesTransform;
            leavesTransform.setTranslation(Vector3(0.0f, level - 0.5f, 0.0f) + levelOffsets[levelIndex]);
            leavesTransform.setRotation(Quaternion::fromAngleAxis(PI, Vector3(1.0f, 0.0f, 0.0f))
                * Quaternion::fromAngleAxis(randFloat() * PI * 2.0f, Vector3(0.0f, 1.0f, 0.0f))
                * Quaternion::fromAngleAxis(PI  * randFloat() / 3.0f, Vector3(1.0f, 0.0f, 0.0f)));
            leavesTransform.setScale(Vector3(2.0f, 2.0f, 2.0f));
            leaves->transformBy(leavesTransform.getMatrix());
            leaves->updateVertexBuffer();

            // Add to the list of leaves
            leavesMeshes.push_back(leaves);
        }

        // Combine the leaves (this is an optimisation step, to reduce draw call count)
        _leavesMesh = Mesh::combineMeshes(leavesMeshes);

        // Clean up
        for (Mesh* mesh : leavesMeshes) {
            delete mesh;
        }
    }

    // Generate all the sublevels
    if (subLevels > 0) {
        size_t subLevelsCount = static_cast<size_t>(ceil(initialSubLevels * (static_cast<float>(subLevels) / static_cast<float>(initialSubLevels))));
        for (size_t i = 0; i < subLevelsCount; i++) {
            // Pick a random level for the branch to be on
            float level = (static_cast<float>(levels)* 0.3f * randFloat()) + (static_cast<float>(levels) * 0.2f);
            float levelDiff = level - floor(level);
            size_t levelIndex = static_cast<size_t>(floor(level));
            Vector3 levelOffsetDiff = levelOffsets[levelIndex];
            if ((levelIndex + 1) < levels) {
                levelOffsetDiff = levelOffsets[levelIndex] + ((levelOffsets[levelIndex + 1] - levelOffsets[levelIndex]) * levelDiff);
            }
            float branchStartRadius = (startLevel * (1.0f - (static_cast<float>(levelIndex) / static_cast<float>(levels)))) - 0.1f;

            // Create a sub branch
            TreeBranch* subBranch = new TreeBranch(true, levels - (subLevels - initialSubLevels) - 2, leavesCount, initialSubLevels, subLevels - 1, branchStartRadius,
                barkMaterial, leavesMaterial);

            // Translate the branch
            subBranch->getLocalTransform().setTranslation(Vector3(0.0f, level, 0.0f) + levelOffsetDiff);
            subBranch->getLocalTransform().setRotation(Quaternion::fromAngleAxis((PI / 5.0f) * (1.0f - (randFloat() * 2.0f)), Vector3(1.0f, 0.0f, 0.0f))
                * Quaternion::fromAngleAxis((PI * 4.0f) * randFloat(), Vector3(0.0f, 1.0f, 0.0f)));

            // Add the branch
            addChild(subBranch);
        }
    }
}

TreeBranch::~TreeBranch()
{
    delete _branchMesh;
    if (_leavesMesh != nullptr) {
        delete _leavesMesh;
    }
}

void TreeBranch::addMeshes(vector<pair<Mesh*, Matrix4x4>> &branches, vector<pair<Mesh*, Matrix4x4>> &leaves)
{
    branches.push_back(make_pair(_branchMesh, getWorldTransform().getMatrix()));
    if (_leavesMesh != nullptr) {
        leaves.push_back(make_pair(_leavesMesh, getWorldTransform().getMatrix()));
    }

    for (SceneObject* sceneChild : getChildren()) {
        TreeBranch* branchChild = reinterpret_cast<TreeBranch*>(sceneChild);
        branchChild->addMeshes(branches, leaves);
    }
}

void TreeBranch::draw(float deltaTime, float totalTime)
{
    // Draw the branch
    _barkMaterial->draw(getWorldTransform().getMatrix(), totalTime);
    _branchMesh->draw(deltaTime, totalTime);

    // Draw the leaves, if we have them
    if (_leavesMesh != nullptr) {
        _leavesMaterial->draw(getWorldTransform().getMatrix(), totalTime);
        _leavesMesh->draw(deltaTime, totalTime);
    }

    // Draw all children
    SceneObject::draw(deltaTime, totalTime);
}
