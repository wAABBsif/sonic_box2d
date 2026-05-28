#include "body.hpp"

#include "box2d/box2d.h"
#include "box2d/types.h"
#include "game/game.hpp"

using namespace sb2d::phys;

static b2BodyType s_b2_type_from_body_type(body::body_type type)
{
	switch (type)
	{
		case body::body_type::STATIC_BODY:
			return b2_staticBody;
		case body::body_type::KINEMATIC_BODY:
			return b2_kinematicBody;
		case body::body_type::DYNAMIC_BODY:
			return b2_dynamicBody;
	}

	return b2_staticBody;
}

body::body(const body_type type, const glm::vec2 position, const float angle)
{
	b2BodyDef def = b2DefaultBodyDef();
	def.type = s_b2_type_from_body_type(type);
	def.position = b2_from_glm(position);
	def.rotation = b2MakeRot(angle);

	id = b2CreateBody(game::get_world().get_box2d_id(), &def);
}

body::~body()
{
	b2DestroyBody(id);
}

glm::vec2 body::get_position() const
{
	return glm_from_b2(b2Body_GetPosition(id));
}

float body::get_rotation() const
{
	return b2Rot_GetAngle(b2Body_GetRotation(id));
}

void body::set_position_and_rotation(const glm::vec2 pos, const float rot) const
{
	b2Body_SetTransform(id, b2_from_glm(pos), b2MakeRot(rot));
}

glm::vec2 body::get_velocity() const
{
	return glm_from_b2(b2Body_GetLinearVelocity(id));
}

void body::set_velocity(const glm::vec2 value) const
{
	b2Body_SetLinearVelocity(id, b2_from_glm(value));
}

float body::get_angular_velocity() const
{
	return b2Body_GetAngularVelocity(id);
}

void body::set_angular_velocity(const float value) const
{
	b2Body_SetAngularVelocity(id, value);
}

void body::apply_force(const glm::vec2 force, const glm::vec2 point) const
{
	if (point.x == NAN && point.y == NAN)
		b2Body_ApplyForceToCenter(id, b2_from_glm(force), true);
	else
		b2Body_ApplyForce(id, b2_from_glm(force), b2_from_glm(point), true);
}

void body::apply_torque(const float torque) const
{
	b2Body_ApplyTorque(id, torque, true);
}

void body::apply_impulse(const glm::vec2 impulse, const glm::vec2 point) const
{
	if (point.x == NAN && point.y == NAN)
		b2Body_ApplyLinearImpulseToCenter(id, b2_from_glm(impulse), true);
	else
		b2Body_ApplyLinearImpulse(id, b2_from_glm(impulse), b2_from_glm(point), true);
}

void body::apply_angular_impulse(const float impulse) const
{
	b2Body_ApplyAngularImpulse(id, impulse, true);
}