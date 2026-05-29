#include "collision_box.hpp"

#include "box2d/box2d.h"
#include "phys/phys.hpp"

using namespace sb2d::phys;

collision_box::collision_box(const float density, const float friction, const float bounce, const glm::vec2 radius, const glm::vec2 center, const float rotation)
	: collision_shape(density, friction, bounce), box(b2MakeOffsetBox(radius.x, radius.y, b2_from_glm(center), b2MakeRot(rotation)))
{}
