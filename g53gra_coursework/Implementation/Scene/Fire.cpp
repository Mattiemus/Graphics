#include "Implementation/Scene/Fire.hpp"
#include "Engine/Graphics/PrimativeGenerator.hpp"

#define PI 3.14159f

using namespace std;

Fire::Fire(Material* fireMaterial, Material* logsMaterial)
    : _fireMaterial(fireMaterial), _logsMaterial(logsMaterial), _fireA(nullptr), _fireB(nullptr), _logs(nullptr)
{
    auto randFloat = []() { return static_cast<float>(rand()) / static_cast<float>(RAND_MAX); };

    // Create the flames
    vector<Mesh*> flameMeshesA;
    vector<Mesh*> flameMeshesB;
    for (size_t i = 0; i < 5; i++) {
        // Make a rotation transformation
        Transform transA;
        transA.setRotation(Quaternion::fromAngleAxis((4.0f * PI) * (static_cast<float>(i) / 5.0f), Vector3(0.0f, 1.0f, 0.0f)));

        Transform transB;
        transB.setRotation(Quaternion::fromAngleAxis((0.3f * PI) + ((4.0f * PI) * (static_cast<float>(i) / 5.0f)), Vector3(0.0f, 1.0f, 0.0f)));

        // Create and transform the plane
        Mesh* planeA = PrimativeGenerator::generatePlane(Vector3(0.0f, 0.5f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));
        planeA->transformBy(transA.getMatrix());
        flameMeshesA.push_back(planeA);

        Mesh* planeB = PrimativeGenerator::generatePlane(Vector3(0.0f, 0.35f, 0.0f), Vector3(1.0f, 0.65f, 1.0f));
        planeB->transformBy(transB.getMatrix());
        flameMeshesB.push_back(planeB);
    }

    // Combine into one big mesh
    _fireA = Mesh::combineMeshes(flameMeshesA);
    _fireA->_isDoubleSided = true;
    _fireB = Mesh::combineMeshes(flameMeshesB);
    _fireB->_isDoubleSided = true;

    // Clean up
    for (Mesh* mesh : flameMeshesA) {
        delete mesh;
    }
    for (Mesh* mesh : flameMeshesB) {
        delete mesh;
    }

    // Create some logs
    vector<Mesh*> logMeshes;
    float totalLogs = 5.0f;
    for (size_t i = 0; i < 5; i++) {
        // Compute the rotation
        float theta = (2.0f * PI * i) / totalLogs;
        float x = sin(theta);
        float y = cos(theta);

        // Make a rotation transformation
        Transform logTrans;
        logTrans.setRotation(Quaternion::fromAngleAxis(theta - (PI / 2.0f), Vector3(0.0f, 1.0f, 0.0f))
            * Quaternion::fromAngleAxis(0.25f * PI, Vector3(0.0f, 0.0f, 1.0f)));
        logTrans.setTranslation(Vector3(0.3f * x, 0.0f, 0.3f * y));

        // Create and transform the log
        Mesh* log = PrimativeGenerator::generateCylinder(Vector3(0.0f, 0.2f, 0.0f), Vector3(0.15f, 0.4f, 0.15f), 8, 1.0f, 1.0f, true);
        log->transformBy(logTrans.getMatrix());
        log->updateVertexBuffer();
        logMeshes.push_back(log);
    }

    // Combine
    _logs = Mesh::combineMeshes(logMeshes);

    // Clean up
    for (Mesh* mesh : logMeshes) {
        delete mesh;
    }
}

Fire::~Fire()
{
    delete _fireA;
    delete _fireB;
}

void Fire::draw(float deltaTime, float totalTime)
{
    getLocalTransform().setScale(Vector3(1.5f, 2.0f * (0.5f + ((1.0f + sin(totalTime * 50.0f)) * 0.005f)), 1.5f));
    _fireMaterial->draw(getWorldTransform().getMatrix(), totalTime);
    _fireA->draw(deltaTime, totalTime);
    _fireB->draw(deltaTime, totalTime);

    getLocalTransform().setScale(Vector3(1.5f, 1.5f, 1.5f));
    _logsMaterial->draw(getWorldTransform().getMatrix(), totalTime);
    _logs->draw(deltaTime, totalTime);

    SceneObject::draw(deltaTime, totalTime);
}