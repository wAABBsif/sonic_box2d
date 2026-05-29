#include "collision_circle.hpp"
#include "phys/phys.hpp"

using namespace sb2d::phys;

collision_circle::collision_circle(const float density, const float friction, const float bounce, const float radius, const glm::vec2 center)
    : collision_shape(density, friction, bounce), circle((b2Circle){b2_from_glm(center), radius})
{}
