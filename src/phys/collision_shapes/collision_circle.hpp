#pragma once
#include "glm/vec2.hpp"
#include "phys/collision_shape.hpp"

namespace sb2d::phys
{
    class collision_circle : public collision_shape
    {
    protected:
        b2Circle circle;
    public:
        collision_circle(const float density, const float friction, const float bounce, const float radius, const glm::vec2 center);
    };
}
