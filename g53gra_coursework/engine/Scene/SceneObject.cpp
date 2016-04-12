#include "Engine/Scene/SceneObject.hpp"

#include <algorithm>

using namespace std;

SceneObject::SceneObject()
    : _parent(nullptr)
{
}

SceneObject::~SceneObject()
{
    for (SceneObject* child : _children) {
        delete child;
    }

    if (_parent != nullptr) {
        //_parent->removeChild(this);
    }
}

void SceneObject::addChild(SceneObject* child)
{
    child->_parent = this;
    _children.push_back(child);
}

void SceneObject::removeChild(SceneObject* child)
{
    auto it = find(_children.begin(), _children.end(), child);
    if (it != _children.end()) {
        child->_parent = nullptr;
        _children.erase(it);
    }
}

void SceneObject::draw(float deltaTime, float totalTime)
{
    for (auto it = _children.begin(); it != _children.end(); ++it) {
        (*it)->draw(deltaTime, totalTime);
    }
}
