#pragma once
#include "box2d/id.h"
#include "box2d/types.h"
#include "glm/glm.hpp"

namespace sb2d::phys
{
	class collision_shape
	{
	public:
		enum class shape_type : uint8_t
		{
			INVALID,
			BOX,
			CIRCLE,
			CAPSULE
		} type;

        float density;
        float friction;
        float bounce;
        
        struct box_def
        {
            glm::vec2 center;
            glm::vec2 radius;
        };

        struct circle_def
        {
            glm::vec2 center;
            float radius;
        };

        struct capsule_def
        {
            glm::vec2 center1;
            glm::vec2 center2;
            float radius;
        };

        union
        {
            box_def box;
            circle_def circle;
            capsule_def capsule;
        };


    public:
        collision_shape() = default;
		collision_shape(float density, float friction, float bounce, shape_type type = shape_type::INVALID);
		collision_shape(float density, float friction, float bounce, box_def box);
		collision_shape(float density, float friction, float bounce, circle_def circle);
		collision_shape(float density, float friction, float bounce, capsule_def capsule);
	};
}
