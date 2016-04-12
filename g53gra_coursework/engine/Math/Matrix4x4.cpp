#include "Engine/Math/Matrix4x4.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Quaternion.hpp"

#include <exception>
#include <cmath>
#define PI (3.14159265358979323846)

using namespace std;

Matrix4x4::Matrix4x4()
    : m11(0.0f), m12(0.0f), m13(0.0f), m14(0.0f),
      m21(0.0f), m22(0.0f), m23(0.0f), m24(0.0f),
      m31(0.0f), m32(0.0f), m33(0.0f), m34(0.0f),
      m41(0.0f), m42(0.0f), m43(0.0f), m44(0.0f)
{
}

Matrix4x4::Matrix4x4(float m11, float m12, float m13, float m14,
    float m21, float m22, float m23, float m24,
    float m31, float m32, float m33, float m34,
    float m41, float m42, float m43, float m44)
    : m11(m11), m12(m12), m13(m13), m14(m14), 
      m21(m21), m22(m22), m23(m23), m24(m24),
      m31(m31), m32(m32), m33(m33), m34(m34), 
      m41(m41), m42(m42), m43(m43), m44(m44)
{
}

Matrix4x4::Matrix4x4(const Matrix4x4 &other)
    : m11(other.m11), m12(other.m12), m13(other.m13), m14(other.m14),
      m21(other.m21), m22(other.m22), m23(other.m23), m24(other.m24),
      m31(other.m31), m32(other.m32), m33(other.m33), m34(other.m34),
      m41(other.m41), m42(other.m42), m43(other.m43), m44(other.m44)
{
}

Matrix4x4 Matrix4x4::getIdentity()
{
    return Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::fromScale(const Vector3 &scale)
{
    Matrix4x4 m;
    m.m11 = scale.x;
    m.m12 = 0.0f;
    m.m13 = 0.0f;
    m.m14 = 0.0f;

    m.m21 = 0.0f;
    m.m22 = scale.y;
    m.m23 = 0.0f;
    m.m24 = 0.0f;

    m.m31 = 0.0f;
    m.m32 = 0.0f;
    m.m33 = scale.z;
    m.m34 = 0.0f;

    m.m41 = 0.0f;
    m.m42 = 0.0f;
    m.m43 = 0.0f;
    m.m44 = 1.0f;
    return m;
}

Matrix4x4 Matrix4x4::fromQuaternion(const Quaternion &rot)
{
    float xx = rot.x * rot.x;
    float xy = rot.x * rot.y;
    float xw = rot.x * rot.w;

    float yy = rot.y * rot.y;
    float yw = rot.y * rot.w;
    float yz = rot.y * rot.z;

    float zx = rot.z * rot.x;
    float zz = rot.z * rot.z;
    float zw = rot.z * rot.w;

    Matrix4x4 m;
    m.m11 = 1.0f - (2.0f * (yy + zz));
    m.m12 = 2.0f * (xy + zw);
    m.m13 = 2.0f * (zx - yw);
    m.m14 = 0.0f;

    m.m21 = 2.0f * (xy - zw);
    m.m22 = 1.0f - (2.0f * (zz + xx));
    m.m23 = 2.0f * (yz + xw);
    m.m24 = 0.0f;

    m.m31 = 2.0f * (zx + yw);
    m.m32 = 2.0f * (yz - xw);
    m.m33 = 1.0f - (2.0f * (yy + xx));
    m.m34 = 0.0f;

    m.m41 = 0.0f;
    m.m42 = 0.0f;
    m.m43 = 0.0f;
    m.m44 = 1.0f;
    return m;
}

Matrix4x4 Matrix4x4::fromTranslation(const Vector3 &translation)
{
    Matrix4x4 m;
    m.m11 = 1.0f;
    m.m12 = 0.0f;
    m.m13 = 0.0f;
    m.m14 = 0.0f;

    m.m21 = 0.0f;
    m.m22 = 1.0f;
    m.m23 = 0.0f;
    m.m24 = 0.0f;

    m.m31 = 0.0f;
    m.m32 = 0.0f;
    m.m33 = 1.0f;
    m.m34 = 0.0f;

    m.m41 = translation.x;
    m.m42 = translation.y;
    m.m43 = translation.z;
    m.m44 = 1.0f;
    return m;
}

Matrix4x4 Matrix4x4::createPerspectiveFOVMatrix(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
{
    if ((fieldOfView <= 0.0f) || (fieldOfView >= PI)) {
        throw exception("Field of view out of range, must be between 0 and Pi!");
    }
    if (nearPlaneDistance <= 0.0f) {
        throw exception("Near plane distance cannot be negative!");
    }
    if (farPlaneDistance <= 0.0f) {
        throw exception("Far plane distance cannot be negative!");
    }
    if (nearPlaneDistance >= farPlaneDistance) {
        throw exception("Near plane distance cannot larger than far plane distance!");
    }

    float h = 1.0f / tan(fieldOfView * 0.5f);
    float w = h / aspectRatio;

    Matrix4x4 m;
    m.m11 = w;
    m.m12 = 0.0f;
    m.m13 = 0.0f;
    m.m14 = 0.0f;
    m.m21 = 0.0f;
    m.m22 = h;
    m.m23 = 0.0f;
    m.m24 = 0.0f;
    m.m31 = 0.0f;
    m.m32 = 0.0f;
    m.m33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
    m.m34 = -1.0f;
    m.m41 = 0.0f;
    m.m42 = 0.0f;
    m.m43 = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
    m.m44 = 0.0f;
    return m;
}

Matrix4x4 Matrix4x4::createViewMatrix(const Vector3 &eyePosition, const Vector3 &target, const Vector3 &up)
{
    Vector3 direction = eyePosition - target;
    direction.normalize();

    Vector3 left = Vector3::cross(up, direction);
    left.normalize();

    Vector3 newUp = Vector3::cross(direction, left);
    newUp.normalize();

    Matrix4x4 m;
    m.m11 = left.x;
    m.m12 = newUp.x;
    m.m13 = direction.x;
    m.m14 = 0.0f;
    m.m21 = left.y;
    m.m22 = newUp.y;
    m.m23 = direction.y;
    m.m24 = 0.0f;
    m.m31 = left.z;
    m.m32 = newUp.z;
    m.m33 = direction.z;
    m.m34 = 0.0f;
    m.m41 = -Vector3::dot(left, eyePosition);
    m.m42 = -Vector3::dot(newUp, eyePosition);
    m.m43 = -Vector3::dot(direction, eyePosition);
    m.m44 = 1.0f;
    return m;
}

Matrix4x4 &Matrix4x4::operator =(const Matrix4x4 &other)
{
    m11 = other.m11;
    m12 = other.m12;
    m13 = other.m13;
    m14 = other.m14;

    m21 = other.m21;
    m22 = other.m22;
    m23 = other.m23;
    m24 = other.m24;

    m31 = other.m31;
    m32 = other.m32;
    m33 = other.m33;
    m34 = other.m34;

    m41 = other.m41;
    m42 = other.m42;
    m43 = other.m43;
    m44 = other.m44;
    return *this;
}

Matrix4x4 Matrix4x4::operator *(const Matrix4x4 &other) const
{
    Matrix4x4 m;
    m.m11 = (((m11 * other.m11) + (m12 * other.m21)) + (m13 * other.m31)) + (m14 * other.m41);
    m.m12 = (((m11 * other.m12) + (m12 * other.m22)) + (m13 * other.m32)) + (m14 * other.m42);
    m.m13 = (((m11 * other.m13) + (m12 * other.m23)) + (m13 * other.m33)) + (m14 * other.m43);
    m.m14 = (((m11 * other.m14) + (m12 * other.m24)) + (m13 * other.m34)) + (m14 * other.m44);

    m.m21 = (((m21 * other.m11) + (m22 * other.m21)) + (m23 * other.m31)) + (m24 * other.m41);
    m.m22 = (((m21 * other.m12) + (m22 * other.m22)) + (m23 * other.m32)) + (m24 * other.m42);
    m.m23 = (((m21 * other.m13) + (m22 * other.m23)) + (m23 * other.m33)) + (m24 * other.m43);
    m.m24 = (((m21 * other.m14) + (m22 * other.m24)) + (m23 * other.m34)) + (m24 * other.m44);

    m.m31 = (((m31 * other.m11) + (m32 * other.m21)) + (m33 * other.m31)) + (m34 * other.m41);
    m.m32 = (((m31 * other.m12) + (m32 * other.m22)) + (m33 * other.m32)) + (m34 * other.m42);
    m.m33 = (((m31 * other.m13) + (m32 * other.m23)) + (m33 * other.m33)) + (m34 * other.m43);
    m.m34 = (((m31 * other.m14) + (m32 * other.m24)) + (m33 * other.m34)) + (m34 * other.m44);

    m.m41 = (((m41 * other.m11) + (m42 * other.m21)) + (m43 * other.m31)) + (m44 * other.m41);
    m.m42 = (((m41 * other.m12) + (m42 * other.m22)) + (m43 * other.m32)) + (m44 * other.m42);
    m.m43 = (((m41 * other.m13) + (m42 * other.m23)) + (m43 * other.m33)) + (m44 * other.m43);
    m.m44 = (((m41 * other.m14) + (m42 * other.m24)) + (m43 * other.m34)) + (m44 * other.m44);
    return m;
}