#ifndef ENGINE_MATH_MATRIX_HPP
#define ENGINE_MATH_MATRIX_HPP

class Vector3;
class Quaternion;

class Matrix4x4
{
public:
    float m11;
    float m12;
    float m13;
    float m14;
    float m21;
    float m22;
    float m23;
    float m24;
    float m31;
    float m32;
    float m33;
    float m34;
    float m41;
    float m42;
    float m43;
    float m44;

    Matrix4x4();
    Matrix4x4(float m11, float m12, float m13, float m14,
        float m21, float m22, float m23, float m24,
        float m31, float m32, float m33, float m34,
        float m41, float m42, float m43, float m44);
    Matrix4x4(const Matrix4x4 &other);

    static Matrix4x4 getIdentity();

    static Matrix4x4 fromScale(const Vector3 &scale);
    static Matrix4x4 fromQuaternion(const Quaternion &rot);
    static Matrix4x4 fromTranslation(const Vector3 &translation);

    static Matrix4x4 createPerspectiveFOVMatrix(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
    static Matrix4x4 createViewMatrix(const Vector3 &eyePosition, const Vector3 &target, const Vector3 &up);

    Matrix4x4 &operator =(const Matrix4x4 &other);
    Matrix4x4 operator *(const Matrix4x4 &other) const;
};

#endif