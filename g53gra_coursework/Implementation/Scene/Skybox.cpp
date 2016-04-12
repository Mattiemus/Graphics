#include "Implementation/Scene/Skybox.hpp"
#include "Engine/Graphics/PrimativeGenerator.hpp"

#define PI 3.14159f

using namespace std;

Skybox::Skybox(Material* front, Material* back, Material* top, Material* left, Material* right)
    : _frontMaterial(front), _backMaterial(back), _topMaterial(top), _leftMaterial(left), _rightMaterial(right),
      _front(nullptr), _back(nullptr), _top(nullptr), _left(nullptr), _right(nullptr)
{
    _front = PrimativeGenerator::generatePlane(Vector3(0.0f, 0.0f, 0.5f), Vector3(1.0f, 1.0f, 1.0f));
    _back = PrimativeGenerator::generatePlane(Vector3(0.0f, 0.0f, -0.5f), Vector3(1.0f, 1.0f, 1.0f));
    
    Transform topTrans;
    topTrans.setRotation(Quaternion::fromAngleAxis(-(PI / 2.0f), Vector3(1.0f, 0.0f, 0.0f)));
    _top = PrimativeGenerator::generatePlane(Vector3(0.0f, 0.0f, 0.5f), Vector3(1.0f, 1.0f, 1.0f));
    _top->transformBy(topTrans.getMatrix());
    _top->updateVertexBuffer();

    Transform sidesTrans;
    sidesTrans.setRotation(Quaternion::fromAngleAxis(PI / 2.0f, Vector3(0.0f, 1.0f, 0.0f)));
    _left = PrimativeGenerator::generatePlane(Vector3(0.0f, 0.0f, 0.5f), Vector3(1.0f, 1.0f, 1.0f));
    _left->transformBy(sidesTrans.getMatrix());
    _left->updateVertexBuffer();
    _right = PrimativeGenerator::generatePlane(Vector3(0.0f, 0.0f, -0.5f), Vector3(1.0f, 1.0f, 1.0f));
    _right->transformBy(sidesTrans.getMatrix());
    _right->updateVertexBuffer();
}

Skybox::~Skybox()
{
    delete _front;
    delete _back;
    delete _top;
    delete _left;
    delete _right;
}

void Skybox::draw(float deltaTime, float totalTime)
{
    _frontMaterial->draw(getWorldTransform().getMatrix(), totalTime);
    _front->draw(deltaTime, totalTime);

    _backMaterial->draw(getWorldTransform().getMatrix(), totalTime);
    _back->draw(deltaTime, totalTime);

    _topMaterial->draw(getWorldTransform().getMatrix(), totalTime);
    _top->draw(deltaTime, totalTime);

    _leftMaterial->draw(getWorldTransform().getMatrix(), totalTime);
    _left->draw(deltaTime, totalTime);

    _rightMaterial->draw(getWorldTransform().getMatrix(), totalTime);
    _right->draw(deltaTime, totalTime);

    SceneObject::draw(deltaTime, totalTime);
}