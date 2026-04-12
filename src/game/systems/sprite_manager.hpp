#pragma once
#include "game/system.hpp"

namespace sb2d::game::systems
{
    struct sprite_manager : public system<sprite_manager>
    {
        static void init();

        void iterate(std::map<entity_id, entity>::iterator& it) override;
    };
}
