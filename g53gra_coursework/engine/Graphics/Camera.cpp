#include "Engine/Graphics/Camera.hpp"

Camera::Camera()
    : _up(0.0f, 1.0f, 0.0f), _right(1.0f, 0.0f, 0.0f)
{
    recompute();
}

void Camera::lookAt(const Vector3 &target, const Vector3 &worldUpVector)
{
    // Compute the world up vector
    Vector3 worldUp = worldUpVector;
    worldUp.normalize();
    if (worldUp.x == 0.0f && worldUp.y == 0.0f && worldUp.z == 0.0f) {
        worldUp = Vector3(0.0f, 1.0f, 0.0f);
    }

    // Compute the backwards vector
    Vector3 backward = _position - target;
    backward.normalize();
    _direction = Vector3(-backward.x, -backward.y, -backward.z);

    // Compute the right vector
    _right = Vector3::cross(worldUp, backward);
    _right.normalize();

    // Compute the up vector
    _up = Vector3::cross(backward, _right);

    // Finally we recompute the view matrix
    recompute();
}

void Camera::setProjection(float fieldOfView, float aspectRatio, float near, float far)
{
    // Create a field of view projection matrix
    _projection = Matrix4x4::createPerspectiveFOVMatrix(fieldOfView, aspectRatio, near, far);
}

void Camera::recompute()
{
    _view = Matrix4x4::createViewMatrix(_position, _position + _direction, _up);
}