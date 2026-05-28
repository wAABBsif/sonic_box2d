#include "world.hpp"
#include "box2d/box2d.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"

using namespace sb2d::phys;

world::world(const float step_time, const int substep_count, const glm::vec2 gravity)
    : step_time(step_time), substep_count(substep_count), accumulator(0)
{
    b2WorldDef def = b2DefaultWorldDef();
    def.gravity = b2_from_glm(gravity);

    this->id = b2CreateWorld(&def);
}

world::~world()
{
    b2DestroyWorld(id);
}

void world::update()
{
    while (accumulator >= step_time)
    {
        accumulator -= step_time;
        b2World_Step(id, step_time, substep_count);
    }
}

b2WorldId world::get_box2d_id() const
{
    return this->id;
}
