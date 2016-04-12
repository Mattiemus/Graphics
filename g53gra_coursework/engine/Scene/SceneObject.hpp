#ifndef ENGINE_SCENE_SCENEOBJECT_HPP
#define ENGINE_SCENE_SCENEOBJECT_HPP

#include "Engine/Core/Drawable.hpp"
#include "Engine/Math/Transform.hpp"

#include <vector>

class SceneObject : public Drawable
{
public:
    SceneObject();
    SceneObject(const SceneObject &other) = delete;
    virtual ~SceneObject();

    Transform &getLocalTransform()
    {
        return _localTransform;
    }

    const Transform &getLocalTransform() const
    {
        return _localTransform;
    }

    Transform getWorldTransform()
    {
        if (_parent != nullptr) {
            Transform worldTransform = _localTransform;
            worldTransform.combine(_parent->getWorldTransform());
            return worldTransform;
        } else {
            return _localTransform;
        }
    }

    SceneObject* getParent()
    {
        return _parent;
    }

    std::vector<SceneObject*> &getChildren()
    {
        return _children;
    }

    const std::vector<SceneObject*> &getChildren() const
    {
        return _children;
    }

    void addChild(SceneObject* child);
    void removeChild(SceneObject* child);
    
    virtual void draw(float deltaTime, float totalTime);
    
    SceneObject &operator =(const SceneObject &other) = delete;

protected:
    SceneObject* _parent;
    std::vector<SceneObject*> _children;
    Transform _localTransform;
};

#endif