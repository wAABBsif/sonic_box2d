#include "body.hpp"

#include "box2d/box2d.h"
#include "box2d/types.h"
#include "game/game.hpp"
#include "phys/collision_shape.hpp"
#include "phys/phys.hpp"

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
    : is_active(false)
{
	b2BodyDef def = b2DefaultBodyDef();
	def.type = s_b2_type_from_body_type(type);
	def.position = b2_from_glm(position);
	def.rotation = b2MakeRot(angle);

	id = b2CreateBody(game::get_world().get_box2d_id(), &def);
}

body::body(const body& b)
    : id(b.id), is_active(false)
{}

body::body(const body&& b)
    : id(b.id), is_active(false)
{}

body::~body()
{
    if (is_active)
	    b2DestroyBody(id);
}

body::body_type body::get_body_type()
{
    switch (b2Body_GetType(id))
    {
        case b2_staticBody:
            return body_type::STATIC_BODY;
        case b2_kinematicBody:
            return body_type::KINEMATIC_BODY;
        case b2_dynamicBody:
            return body_type::DYNAMIC_BODY;
        default:
            return body_type::STATIC_BODY;
    }
}

void body::set_body_type(const body::body_type value)
{
    b2BodyType body_type;
    switch (value)
    {
        case body_type::STATIC_BODY:
            body_type = b2_staticBody;
            break;
        case body_type::KINEMATIC_BODY:
            body_type = b2_kinematicBody;
            break;
        case body_type::DYNAMIC_BODY:
            body_type = b2_dynamicBody;
            break;
        default:
            return;
    }

    b2Body_SetType(id, body_type);
}

std::string body::get_body_type_as_string(body_type type)
{
    if (type == body_type::INVALID_BODY)
        type = get_body_type();

    switch (type)
    {
        case body_type::STATIC_BODY:
            return "Static";
        case body_type::KINEMATIC_BODY:
            return "Kinematic";
        case body_type::DYNAMIC_BODY:
            return "Dynamic";
        default:
            return "Invalid";
    }
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

int body::get_shape_count()
{
    return b2Body_GetShapeCount(id);
}

void body::get_shapes(collision_shape* shapes, int count)
{
    if (count < 0)
        count = get_shape_count();
    b2ShapeId* shape_ids = new b2ShapeId[count];
    b2Body_GetShapes(id, shape_ids, count);
    for (int i = 0; i < count; i++)
    {
        b2SurfaceMaterial mat = b2Shape_GetSurfaceMaterial(shape_ids[i]);
        shapes[i].density = b2Shape_GetDensity(shape_ids[i]);
        shapes[i].friction = mat.friction;
        shapes[i].bounce = mat.restitution;
        
        switch (b2Shape_GetType(shape_ids[i]))
        {
            case b2_polygonShape:
            {
                b2Polygon poly = b2Shape_GetPolygon(shape_ids[i]);
                shapes[i].box.center = glm_from_b2(poly.centroid);
                shapes[i].box.radius = glm_from_b2(poly.vertices[2]);
                break;
            }
            case b2_circleShape:
            {
                b2Circle circ = b2Shape_GetCircle(shape_ids[i]);
                shapes[i].circle.center = glm_from_b2(circ.center);
                shapes[i].circle.radius = circ.radius;
                break;
            }
            case b2_capsuleShape:
            {
                b2Capsule caps = b2Shape_GetCapsule(shape_ids[i]);
                shapes[i].capsule.center1 = glm_from_b2(caps.center1);
                shapes[i].capsule.center2 = glm_from_b2(caps.center2);
                shapes[i].capsule.radius = caps.radius;
                break;
            }
            default:
                break;
        }
    }
}

void body::add_shape(collision_shape shape)
{
    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = shape.density;
    shape_def.material.friction = shape.friction;
    shape_def.material.restitution = shape.bounce;

    switch (shape.type)
    {
        case collision_shape::shape_type::BOX:
        {
            b2Polygon box = b2MakeOffsetBox(shape.box.radius.x, shape.box.radius.y, b2_from_glm(shape.box.center), b2MakeRot(0));
            b2CreatePolygonShape(id, &shape_def, &box);
            break;
        }
        case collision_shape::shape_type::CIRCLE:
        {
            b2Circle circle = (b2Circle){b2_from_glm(shape.circle.center), shape.circle.radius};
            b2CreateCircleShape(id, &shape_def, &circle);
            break;
        }
        case collision_shape::shape_type::CAPSULE:
        {
            b2Capsule capsule = (b2Capsule){b2_from_glm(shape.capsule.center1), b2_from_glm(shape.capsule.center2), shape.capsule.radius};
            b2CreateCapsuleShape(id, &shape_def, &capsule);
            break;
        }
        default:
            break;
    }
}

void body::remove_shape(int idx)
{
    b2ShapeId* shape_ids = new b2ShapeId[idx + 1];
    b2Body_GetShapes(id, shape_ids, idx + 1);
    b2ShapeId& shape_id = shape_ids[idx];

    b2DestroyShape(shape_id, true);
}

void body::set_shape(collision_shape shape, int idx)
{
    b2ShapeId* shape_ids = new b2ShapeId[idx + 1];
    b2Body_GetShapes(id, shape_ids, idx + 1);
    b2ShapeId& shape_id = shape_ids[idx];

    b2SurfaceMaterial mat = b2DefaultSurfaceMaterial();
    mat.friction = shape.friction;
    mat.restitution = shape.bounce;
    b2Shape_SetDensity(shape_id, shape.density, true);
    b2Shape_SetSurfaceMaterial(shape_id, &mat); 
    switch (shape.type)
    {
        case collision_shape::shape_type::BOX:
        {
            b2Polygon box = b2MakeOffsetBox(shape.box.radius.x, shape.box.radius.y, b2_from_glm(shape.box.center), b2MakeRot(0));
            b2Shape_SetPolygon(shape_id, &box);
            break;
        }
        case collision_shape::shape_type::CIRCLE:
        {
            b2Circle circle = (b2Circle){b2_from_glm(shape.circle.center), shape.circle.radius};
            b2Shape_SetCircle(shape_id, &circle);
            break;
        }
        case collision_shape::shape_type::CAPSULE:
        {
            b2Capsule capsule = (b2Capsule){b2_from_glm(shape.capsule.center1), b2_from_glm(shape.capsule.center2), shape.capsule.radius};
            b2Shape_SetCapsule(shape_id, &capsule);
            break;
        }
        default:
            break;
    }
}
