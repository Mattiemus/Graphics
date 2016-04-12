#include "Engine/Math/Transform.hpp"

Transform::Transform()
    : _translation(Vector3(0.0f, 0.0f, 0.0f)), _rotation(Quaternion(0.0f, 0.0f, 0.0f, 1.0f)), _scale(Vector3(1.0f, 1.0f, 1.0f))
{
    computeMatrix();
}

Transform::Transform(Vector3 translation, Quaternion rotation, Vector3 scale)
    : _translation(translation), _rotation(rotation), _scale(scale)
{
    computeMatrix();
}

Transform::Transform(const Transform &other)
    : _matrix(other._matrix), _translation(other._translation), _rotation(other._rotation), _scale(other._scale)
{
}

void Transform::combine(const Transform &parent)
{
    _scale = _scale * parent._scale;
    _rotation = _rotation * parent._rotation;
    _translation = _translation * parent._scale; 
    _translation.transform(parent._rotation);
    _translation = _translation + parent._translation;

    computeMatrix();
}

void Transform::computeMatrix()
{
    _matrix = Matrix4x4::fromScale(_scale) * Matrix4x4::fromQuaternion(_rotation) * Matrix4x4::fromTranslation(_translation);
}

Transform &Transform::operator =(const Transform &other)
{
    _matrix = other._matrix;
    _translation = other._translation;
    _rotation = other._rotation;
    _scale = other._scale;
    return *this;
}