#ifndef IMPLEMENTATION_SCENE_BENCH_HPP
#define IMPLEMENTATION_SCENE_BENCH_HPP

#include "Implementation/Scene/Terrain.hpp"
#include "Engine/Scene/SceneObject.hpp"
#include "Engine/Graphics/Material.hpp"
#include "Engine/Graphics/Mesh.hpp"

class Bench : public SceneObject
{
public:
    Bench(Material* legsMaterial, Material* seatMaterial);
    Bench(const Bench &other) = delete;
    virtual ~Bench();

    virtual void draw(float deltaTime, float totalTime);

    Bench &operator =(const Bench &other) = delete;

private:
    Material* _legsMaterial;
    Material* _seatMaterial;
    Mesh* _legs;
    Mesh* _seat;
};

#endif