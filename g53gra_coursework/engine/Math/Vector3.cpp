#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Quaternion.hpp"
#include "Engine/Math/Matrix4x4.hpp"

#include <cmath>

Vector3::Vector3()
    : x(0.0f), y(0.0f), z(0.0f)
{
}

Vector3::Vector3(float xVal, float yVal, float zVal)
    : x(xVal), y(yVal), z(zVal)
{
}

Vector3::Vector3(const Vector3 &other)
    : x(other.x), y(other.y), z(other.z)
{
}

float Vector3::length() const
{
    return sqrt((x * x) + (y * y) + (z * z));
}

void Vector3::transform(const Quaternion &q)
{
    float wx2 = q.w * q.x * 2;
    float wy2 = q.w * q.y * 2;
    float wz2 = q.w * q.z * 2;

    float xx2 = q.x * q.x * 2;
    float xy2 = q.x * q.y * 2;
    float xz2 = q.x * q.z * 2;

    float yy2 = q.y * q.y * 2;
    float yz2 = q.y * q.z * 2;

    float zz2 = q.z * q.z * 2;

    float xv = ((x * ((1.0f - yy2) - zz2)) + (y * (xy2 - wz2))) + (z * (xz2 + wy2));
    float yv = ((x * (xy2 + wz2)) + (y * ((1.0f - xx2) - zz2))) + (z * (yz2 - wx2));
    float zv = ((x * (xz2 - wy2)) + (y * (yz2 + wx2))) + (z * ((1.0f - xx2) - yy2));

    x = xv;
    y = yv;
    z = zv;
}

void Vector3::transform(const Matrix4x4 &m)
{
    float xv = (x * m.m11) + (y * m.m21) + (z * m.m31) + m.m41;
    float yv = (x * m.m12) + (y * m.m22) + (z * m.m32) + m.m42;
    float zv = (x * m.m13) + (y * m.m23) + (z * m.m33) + m.m43;

    x = xv;
    y = yv;
    z = zv;
}

void Vector3::normalize()
{
    float inverseLength = 1.0f / sqrt((x * x) + (y * y) + (z * z));
    x *= inverseLength;
    y *= inverseLength;
    z *= inverseLength;
}

float Vector3::dot(const Vector3 &a, const Vector3 &b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vector3 Vector3::cross(const Vector3 &a, const Vector3 &b)
{
    Vector3 v;
    v.x = (a.y * b.z) - (a.z * b.y);
    v.y = (a.z * b.x) - (a.x * b.z);
    v.z = (a.x * b.y) - (a.y * b.x);
    return v;
}

Vector3 &Vector3::operator =(const Vector3 &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

Vector3 Vector3::operator +(const Vector3 &other) const
{
    Vector3 v;
    v.x = x + other.x;
    v.y = y + other.y;
    v.z = z + other.z;
    return v;
}

Vector3 Vector3::operator -(const Vector3 &other) const
{
    Vector3 v;
    v.x = x - other.x;
    v.y = y - other.y;
    v.z = z - other.z;
    return v;
}

Vector3 Vector3::operator *(float scale) const
{
    Vector3 v;
    v.x = x * scale;
    v.y = y * scale;
    v.z = z * scale;
    return v;
}

Vector3 Vector3::operator *(const Vector3 &other) const
{
    Vector3 v;
    v.x = x * other.x;
    v.y = y * other.y;
    v.z = z * other.z;
    return v;
}

Vector3 Vector3::operator / (float scale) const
{
    Vector3 v;
    v.x = x / scale;
    v.y = y / scale;
    v.z = z / scale;
    return v;
}