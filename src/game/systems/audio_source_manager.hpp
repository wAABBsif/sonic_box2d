#pragma once
#include "game/system.hpp"

namespace sb2d::game::systems
{
    class audio_source_manager : public system<audio_source_manager>
    {
    public:
        static void init();
        
        void iterate(std::map<entity_id, entity>::iterator& it) override;
    };
}
