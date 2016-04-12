#ifndef ENGINE_MATH_QUATERNION_HPP
#define ENGINE_MATH_QUATERNION_HPP

class Vector3;

class Quaternion
{
public:
    float x;
    float y;
    float z;
    float w;

    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(const Quaternion &other);

    static Quaternion fromAngleAxis(float angle, const Vector3 &axis);

    Quaternion &operator =(const Quaternion &other);
    Quaternion operator *(const Quaternion &other) const;
};

#endif