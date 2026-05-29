#pragma once
#include "glm/vec2.hpp"
#include "phys/collision_shape.hpp"

namespace sb2d::phys
{
	class collision_box : public collision_shape
	{
	protected:
		b2Polygon box;
	public:
		collision_box(float density, float friction, float bounce, glm::vec2 radius, glm::vec2 center = glm::vec2(0.0f), float rotation = 0);
	};
}
