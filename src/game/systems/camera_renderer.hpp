#pragma once
#include "game/system.hpp"

namespace sb2d::game::systems
{
    class camera_renderer : public system<camera_renderer>
    {
    public:
        static void init();
        void iterate(std::map<entity_id, entity>::iterator& it) override;
    };
}
