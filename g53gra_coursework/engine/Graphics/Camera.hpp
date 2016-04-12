#ifndef CORE_GRAPHICS_CAMERA_HPP
#define CORE_GRAPHICS_CAMERA_HPP

#include "Engine/Math/Matrix4x4.hpp"
#include "Engine/Math/Vector3.hpp"

class Camera
{
public:
    Camera();
    Camera(const Camera &other) = delete;

    Matrix4x4 getView() const
    {
        return _view;
    }

    Matrix4x4 getProjection() const
    {
        return _projection;
    }

    Vector3 getDirection() const
    {
        return _direction;
    }

    void setDirection(const Vector3 &dir)
    {
        _direction = dir;
        recompute();
    }

    Vector3 getPosition() const
    {
        return _position;
    }

    void setPosition(const Vector3 &pos)
    {
        _position = pos;
        recompute();
    }

    Vector3 getUp() const
    {
        return _up;
    }

    void setUp(const Vector3 &up)
    {
        _up = up;
        recompute();
    }

    Vector3 getRight() const
    {
        return _right;
    }

    void setRight(const Vector3 &right)
    {
        _right = right;
        recompute();
    }

    void lookAt(const Vector3 &target, const Vector3 &worldUpVector);
    void setProjection(float fieldOfView, float aspectRatio, float near, float far);

    void recompute();

    Camera &operator =(const Camera &other) = delete;

private:
    Matrix4x4 _view;
    Matrix4x4 _projection;
    Vector3 _position;
    Vector3 _direction;
    Vector3 _up;
    Vector3 _right;
};

#endif