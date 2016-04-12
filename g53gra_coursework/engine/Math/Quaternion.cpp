#include "Engine/Math/Quaternion.hpp"
#include "Engine/Math/Vector3.hpp"

#include <cmath>

Quaternion::Quaternion()
    : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
}

Quaternion::Quaternion(float xVal, float yVal, float zVal, float wVal)
    : x(xVal), y(yVal), z(zVal), w(wVal)
{
}

Quaternion::Quaternion(const Quaternion &other)
    : x(other.x), y(other.y), z(other.z), w(other.w)
{
}

Quaternion Quaternion::fromAngleAxis(float angle, const Vector3 &axis)
{
    Quaternion q;
    q.x = axis.x * sin(angle * 0.5f);
    q.y = axis.y * sin(angle * 0.5f);
    q.z = axis.z * sin(angle * 0.5f);
    q.w = cos(angle * 0.5f);
    return q;
}

Quaternion &Quaternion::operator =(const Quaternion &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

Quaternion Quaternion::operator *(const Quaternion &other) const
{
    Quaternion q;
    q.x = ((x * other.w) + (other.x * w)) + ((y * other.z) - (z * other.y));
    q.y = ((y * other.w) + (other.y * w)) + ((z * other.x) - (x * other.z));
    q.z = ((z * other.w) + (other.z * w)) + ((x * other.y) - (y * other.x));
    q.w = (w * other.w) - (((x * other.x) + (y * other.y)) + (z * other.z));
    return q;
}