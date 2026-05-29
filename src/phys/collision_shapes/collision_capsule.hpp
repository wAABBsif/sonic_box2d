#pragma once
#include "box2d/collision.h"
#include "glm/vec2.hpp"
#include "phys/collision_shape.hpp"

namespace sb2d::phys
{
    class collision_capsule : public collision_shape
    {
    protected:
        b2Capsule capsule;
    public:
        collision_capsule(const float density, const float friction, const float bounce, const float radius, const glm::vec2 center1 = glm::vec2(0, -0.5f), const glm::vec2 center2 = glm::vec2(0, 0.5f));
    };
}
