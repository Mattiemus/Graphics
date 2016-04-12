#ifndef ENGINE_MATH_VECTOR3_HPP
#define ENGINE_MATH_VECTOR3_HPP

class Quaternion;
class Matrix4x4;

class Vector3
{
public:
    float x;
    float y;
    float z;

    Vector3();
    Vector3(float x, float y, float z);
    Vector3(const Vector3 &other);

    float length() const;
    void transform(const Quaternion &q);
    void transform(const Matrix4x4 &m);
    void normalize();

    static float dot(const Vector3 &a, const Vector3 &b);
    static Vector3 cross(const Vector3 &a, const Vector3 &b);

    Vector3 &operator =(const Vector3 &other);
    Vector3 operator +(const Vector3 &other) const;
    Vector3 operator -(const Vector3 &other) const;
    Vector3 operator *(float scale) const;
    Vector3 operator *(const Vector3 &other) const;
    Vector3 operator /(float scale) const;
};

#endif