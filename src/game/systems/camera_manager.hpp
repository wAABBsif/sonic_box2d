#pragma once
#include "game/system.hpp"

namespace sb2d::game::systems
{
    class camera_manager : public system<camera_manager>
    {
    public:
        static void init();
        void iterate(std::map<entity_id, entity>::iterator& it) override;
    };
}
