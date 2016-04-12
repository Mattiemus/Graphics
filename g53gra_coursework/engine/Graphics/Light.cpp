#include "Engine/Graphics/Light.hpp"

Light::Light()
    : _power(1.0f)
{
}

Light::Light(const Light &other)
{
    _position = other._position;
    _color = other._color;
    _colorAmbient = other._colorAmbient;
    _power = other._power;
}

Light &Light::operator =(const Light &other)
{
    _position = other._position;
    _color = other._color;
    _colorAmbient = other._colorAmbient;
    _power = other._power;
    return *this;
}