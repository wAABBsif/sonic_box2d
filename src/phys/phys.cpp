#include "phys.hpp"

using namespace sb2d;
using namespace sb2d::phys;

b2Vec2 phys::b2_from_glm(const glm::vec2 v)
{
	return b2Vec2(v.x, v.y);
}

glm::vec2 phys::glm_from_b2(const b2Vec2 v)
{
	return glm::vec2(v.x, v.y);
}