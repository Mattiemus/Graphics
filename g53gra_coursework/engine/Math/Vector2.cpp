#include "Engine/Math/Vector2.hpp"

#include <cmath>

Vector2::Vector2()
    : x(0.0f), y(0.0f)
{
}

Vector2::Vector2(float xVal, float yVal)
    : x(xVal), y(yVal)
{
}

Vector2::Vector2(const Vector2 &other)
    : x(other.x), y(other.y)
{
}

Vector2 &Vector2::operator =(const Vector2 &other)
{
    x = other.x;
    y = other.y;
    return *this;
}

Vector2 Vector2::operator +(const Vector2 &other) const
{
    Vector2 v;
    v.x = x + other.x;
    v.y = y + other.y;
    return v;
}

Vector2 Vector2::operator -(const Vector2 &other) const
{
    Vector2 v;
    v.x = x - other.x;
    v.y = y - other.y;
    return v;
}

Vector2 Vector2::operator *(const Vector2 &other) const
{
    Vector2 v;
    v.x = x * other.x;
    v.y = y * other.y;
    return v;
}