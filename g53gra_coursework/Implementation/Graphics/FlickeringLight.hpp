#ifndef IMPLEMENTATION_GRAPHICS_FLICKERINGLIGHT_HPP
#define IMPLEMENTATION_GRAPHICS_FLICKERINGLIGHT_HPP

#include "Engine/Graphics/Light.hpp"
#include "Engine/Core/Updatable.hpp"

class FlickeringLight : public Light, public Updatable
{
public:
    FlickeringLight(const Vector4 &minColor, const Vector4 &maxColor);
    FlickeringLight(const FlickeringLight &other) = delete;
    virtual ~FlickeringLight();

    virtual void update(float deltaTime, float totalTime);

    FlickeringLight &operator =(const FlickeringLight &other) = delete;

private:
    Vector4 _minColor;
    Vector4 _maxColor;
};

#endif