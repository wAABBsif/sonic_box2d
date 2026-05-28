#pragma once
#include "box2d/math_functions.h"
#include "glm/vec2.hpp"

namespace sb2d::phys
{
	b2Vec2 b2_from_glm(glm::vec2 v);
	glm::vec2 glm_from_b2(b2Vec2 v);
}
