#include "Engine/Math/Vector4.hpp"

#include <cmath>

Vector4::Vector4()
    : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
}

Vector4::Vector4(float xVal, float yVal, float zVal, float wVal)
    : x(xVal), y(yVal), z(zVal), w(wVal)
{
}

Vector4::Vector4(const Vector4 &other)
    : x(other.x), y(other.y), z(other.z), w(other.w)
{
}

Vector4 &Vector4::operator =(const Vector4 &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

Vector4 Vector4::operator *(float scale) const
{
    Vector4 v;
    v.x = x * scale;
    v.y = y * scale;
    v.z = z * scale;
    v.w = w * scale;
    return v;
}

Vector4 Vector4::operator -(const Vector4 &other) const
{
    Vector4 v;
    v.x = x - other.x;
    v.y = y - other.y;
    v.z = z - other.z;
    v.w = w - other.w;
    return v;
}

Vector4 Vector4::operator +(const Vector4 &other) const
{
    Vector4 v;
    v.x = x + other.x;
    v.y = y + other.y;
    v.z = z + other.z;
    v.w = w + other.w;
    return v;
}