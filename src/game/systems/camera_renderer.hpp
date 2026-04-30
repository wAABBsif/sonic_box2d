#pragma once
#include "game/component.hpp"
#include "game/system.hpp"
#include "gfx/renderer.hpp"
#include "game/components/camera.hpp"

namespace sb2d::game::systems
{
    class camera_renderer : public gfx::renderer<camera_renderer>, public system<camera_renderer>
    {
    public:
        static void init();
        static void terminate();
        static void draw_camera(components::camera& cam, glm::mat3 mat);

        void iterate(std::map<entity_id, entity>::iterator& it) override;
    };
}
