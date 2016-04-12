#ifndef IMPLEMENTATION_SCENE_PLANETSPINNER_HPP
#define IMPLEMENTATION_SCENE_PLANETSPINNER_HPP

#include "Implementation/Scene/Terrain.hpp"
#include "Engine/Scene/SceneObject.hpp"
#include "Engine/Graphics/Material.hpp"
#include "Engine/Graphics/Light.hpp"
#include "Engine/Graphics/Mesh.hpp"

class PlanetSpinner : public SceneObject
{
public:
    PlanetSpinner(Material* centerMaterial, Material* planetsMaterial);
    PlanetSpinner(const PlanetSpinner &other) = delete;
    virtual ~PlanetSpinner();

    virtual void draw(float deltaTime, float totalTime);

    PlanetSpinner &operator =(const PlanetSpinner &other) = delete;

private:
    Material* _centerMaterial;
    Mesh* _center;
    Light* _light;
};

class Planet : public SceneObject
{
public:
    Planet(Material* planetMaterial, float armLength, float speed, bool hasChild);
    Planet(const PlanetSpinner &other) = delete;
    virtual ~Planet();

    virtual void draw(float deltaTime, float totalTime);

    Planet &operator =(const Planet &other) = delete;

private:
    float _rotationalSpeed;
    float _armLength;
    Material* _planetMaterial;
    Mesh* _planet;
};

#endif