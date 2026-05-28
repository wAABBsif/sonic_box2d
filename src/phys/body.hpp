#pragma once
#include <cstdint>
#include <math.h>

#include "box2d/id.h"
#include "glm/vec2.hpp"

namespace sb2d::phys
{
	class body
	{
	private:
		b2BodyId id;
	protected:
		enum class body_type : uint8_t
		{
			STATIC_BODY,
			KINEMATIC_BODY,
			DYNAMIC_BODY
		};

		explicit body(body_type type = body_type::STATIC_BODY, glm::vec2 position = glm::vec2(0, 0), float angle = 0);
		virtual ~body();

		glm::vec2 get_position() const;
		float get_rotation() const;
		void set_position_and_rotation(glm::vec2 pos, float rot) const;

		glm::vec2 get_velocity() const;
		void set_velocity(glm::vec2 value) const;
		float get_angular_velocity() const;
		void set_angular_velocity(float value) const;

		void apply_force(glm::vec2 force, glm::vec2 point = glm::vec2(NAN, NAN)) const;
		void apply_torque(float torque) const;
		void apply_impulse(glm::vec2 impulse, glm::vec2 point = glm::vec2(NAN, NAN)) const;
		void apply_angular_impulse(float impulse) const;
	};
}
