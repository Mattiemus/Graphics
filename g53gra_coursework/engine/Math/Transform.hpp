#ifndef ENGINE_MATH_TRANSFORM_HPP
#define ENGINE_MATH_TRANSFORM_HPP

#include "Engine/Math/Matrix4x4.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Quaternion.hpp"

class Transform
{
public:
    Transform();
    Transform(Vector3 translation, Quaternion rotation, Vector3 scale);
    Transform(const Transform &other);

    const Matrix4x4 &getMatrix() const
    {
        return _matrix;
    }

    const Vector3 &getTranslation() const
    {
        return _translation;
    }

    const Quaternion &getRotation() const
    {
        return _rotation;
    }

    const Vector3 &getScale() const
    {
        return _scale;
    }

    void setTranslation(const Vector3 &translation)
    {
        _translation = translation;
        computeMatrix();
    }

    void setRotation(const Quaternion &rotation)
    {
        _rotation = rotation;
        computeMatrix();
    }

    void setScale(const Vector3 &scale)
    {
        _scale = scale;
        computeMatrix();
    }

    void combine(const Transform &parent);

    Transform &operator =(const Transform &other);

private:
    void computeMatrix();

    Matrix4x4 _matrix;
    Vector3 _translation;
    Quaternion _rotation;
    Vector3 _scale;
};

#endif