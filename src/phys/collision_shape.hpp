#pragma once
#include "box2d/id.h"
#include "box2d/types.h"

namespace sb2d::phys
{
	class collision_shape
	{
	public:
		enum class shape_type
		{
			INVALID,
			BOX,
			CIRCLE,
			CAPSULE
		};

	protected:
		b2ShapeDef def;
		b2ShapeId id;

		collision_shape(float density, float friction, float bounce);
	public:
		~collision_shape();

		shape_type get_shape_type() const;
		float get_density() const;
		float get_friction() const;
		float get_bounce() const;
	};
}
