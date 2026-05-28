#pragma once
#include "phys.hpp"
#include "box2d/id.h"
#include "glm/glm.hpp"

namespace sb2d::phys
{
    class world
    {
    private:
        b2WorldId id;
    public:
        float step_time;
        int substep_count;
    private:
        float accumulator;
    public:
        explicit world(const float step_time = 1.0f / 60.0f, const int substep_count = 4, const glm::vec2 gravity = glm::vec2(0, -9.806f));
        ~world();

        void update();

        b2WorldId get_box2d_id() const;
    };
}
