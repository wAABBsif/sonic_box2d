#include "collision_capsule.hpp"
#include "box2d/collision.h"
#include "phys/phys.hpp"

using namespace sb2d::phys;

collision_capsule::collision_capsule(const float density, const float friction, const float bounce, const float radius, const glm::vec2 center1, const glm::vec2 center2)
    : collision_shape(density, friction, bounce), capsule((b2Capsule){b2_from_glm(center1), b2_from_glm(center2), radius})
{}
