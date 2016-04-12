#ifndef ENGINE_GRAPHICS_PRIMATIVEGENERATOR_HPP
#define ENGINE_GRAPHICS_PRIMATIVEGENERATOR_HPP

#include "Engine/Graphics/Mesh.hpp"
#include "Engine/Math/Vector3.hpp"

class PrimativeGenerator
{
public:
    PrimativeGenerator();
    PrimativeGenerator(const PrimativeGenerator &other) = delete;
    ~PrimativeGenerator();

    static Mesh* generatePlane(const Vector3 &offset, const Vector3 &scale);
    static Mesh* generateCube(const Vector3 &offset, const Vector3 &scale);
    static Mesh* generateCylinder(const Vector3 &offset, const Vector3 &scale, unsigned int radialSegments, float topRadius, float bottomRadius, bool genCaps);
    static Mesh* generateSphere(const Vector3 &offset, const Vector3 &scale, unsigned int heightSegments, unsigned int widthSegments);

    PrimativeGenerator &operator =(const PrimativeGenerator &other) = delete;
};

#endif