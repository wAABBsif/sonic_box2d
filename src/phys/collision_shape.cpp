#include "collision_shape.hpp"

#include "box2d/box2d.h"
#include "input/keyboard.hpp"

using namespace sb2d::phys;

collision_shape::collision_shape(const float density, const float friction, const float bounce)
	: def(b2DefaultShapeDef()), id(b2_nullShapeId)
{
	def.density = density;
	def.material.friction = friction;
	def.material.restitution = bounce;
}

collision_shape::~collision_shape()
{
	b2DestroyShape(id, true);
}

collision_shape::shape_type collision_shape::get_shape_type() const
{
	b2ShapeType b2_type = b2Shape_GetType(id);
	switch (b2_type)
	{
		case b2_polygonShape:
			return b2Shape_GetPolygon(id).count == 4 ? shape_type::BOX : shape_type::INVALID;
		case b2_circleShape:
			return shape_type::CIRCLE;
		case b2_capsuleShape:
			return shape_type::CAPSULE;
		default:
			return shape_type::INVALID;
	}
}

float collision_shape::get_density() const
{
	return b2Shape_GetDensity(id);
}

float collision_shape::get_friction() const
{
	return b2Shape_GetSurfaceMaterial(id).friction;
}

float collision_shape::get_bounce() const
{
	return b2Shape_GetSurfaceMaterial(id).restitution;
}