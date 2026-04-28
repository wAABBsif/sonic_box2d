#pragma once
#include "game/components/sprite.hpp"
#include "game/system.hpp"

namespace sb2d::game::systems
{
    class sprite_renderer : public gfx::renderer<sprite_renderer>, public system<sprite_renderer>
    {
    public:
        static void init();
        static void terminate();
        static void draw(glm::mat3 world_to_screen);

        void iterate(std::map<entity_id, entity>::iterator& it) override;

        static constexpr int capacity = 1024;
    };
}
