#include "collision_shape.hpp"

#include "box2d/box2d.h"
#include "input/keyboard.hpp"

using namespace sb2d::phys;

collision_shape::collision_shape(const float density, const float friction, const float bounce, const shape_type type)
	: density(density), friction(friction), bounce(bounce), type(type)
{}

collision_shape::collision_shape(const float density, const float friction, const float bounce, const box_def box)
    : collision_shape(density, friction, bounce, shape_type::BOX)
{
    this->box = box; 
}

collision_shape::collision_shape(const float density, const float friction, const float bounce, const circle_def circle)
    : collision_shape(density, friction, bounce, shape_type::CIRCLE)
{
    this->circle = circle;
}

collision_shape::collision_shape(const float density, const float friction, const float bounce, const capsule_def capsule)
    : collision_shape(density, friction, bounce, shape_type::CAPSULE)
{
    this->capsule = capsule;
}
