#ifndef CORE_GRAPHICS_LIGHT_HPP
#define CORE_GRAPHICS_LIGHT_HPP

#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Vector4.hpp"

class Light
{
public:
    Light();
    Light(const Light &other);

    Vector3 getPosition() const
    {
        return _position;
    }

    void setPosition(const Vector3 &pos)
    {
        _position = pos;
    }

    Vector4 getColor() const
    {
        return _color;
    }

    void setColor(const Vector4 &color)
    {
        _color = color;
    }

    Vector4 getAmbientColor() const
    {
        return _colorAmbient;
    }

    void setAmbientColor(const Vector4 &ambient)
    {
        _colorAmbient = ambient;
    }

    float getPower() const
    {
        return _power;
    }

    void setPower(float power)
    {
        _power = power;
    }

    Light &operator =(const Light &other);

private:
    Vector3 _position;
    Vector4 _color;
    Vector4 _colorAmbient;
    float _power;
};

#endif