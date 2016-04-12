#include "Implementation/Graphics/FlickeringLight.hpp"

#include <cstdlib>
#include <cmath>

using namespace std;

FlickeringLight::FlickeringLight(const Vector4 &minColor, const Vector4 &maxColor)
    : _minColor(minColor), _maxColor(maxColor)
{
}

FlickeringLight::~FlickeringLight()
{
}

void FlickeringLight::update(float deltaTime, float totalTime)
{
    Vector4 colorDiff = _maxColor - _minColor;
    setColor(_minColor + (colorDiff * abs(sin(totalTime * 5.0f))));
}