#ifndef ENGINE_MATH_VECTOR4_HPP
#define ENGINE_MATH_VECTOR4_HPP

class Vector4
{
public:
    float x;
    float y;
    float z;
    float w;

    Vector4();
    Vector4(float x, float y, float z, float w);
    Vector4(const Vector4 &other);

    Vector4 &operator =(const Vector4 &other);
    Vector4 operator *(float scale) const;
    Vector4 operator -(const Vector4 &other) const;
    Vector4 operator +(const Vector4 &other) const;
};

#endif