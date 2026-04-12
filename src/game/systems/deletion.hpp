#pragma once
#include "game/system.hpp"

namespace sb2d::game::systems
{
    struct deletion : public system<deletion>
    {
        static void init();

        void iterate(std::map<entity_id, entity>::iterator& it) override;
    };
}
