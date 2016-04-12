#ifndef ENGINE_MATH_VECTOR2_HPP
#define ENGINE_MATH_VECTOR2_HPP

class Vector2
{
public:
    float x;
    float y;

    Vector2();
    Vector2(float x, float y);
    Vector2(const Vector2 &other);

    Vector2 &operator =(const Vector2 &other);
    Vector2 operator +(const Vector2 &other) const;
    Vector2 operator -(const Vector2 &other) const;
    Vector2 operator *(const Vector2 &other) const;
};

#endif