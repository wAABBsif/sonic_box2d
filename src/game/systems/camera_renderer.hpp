#pragma once
#include "game/component.hpp"
#include "game/system.hpp"
#include "gfx/renderer.hpp"
#include "game/components/camera.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace sb2d::game::systems
{
    class camera_renderer : public gfx::renderer<camera_renderer>, public system<camera_renderer>
    {
    private:
        static inline entity_id s_main_camera;
    public:
        static void init();
        static void terminate();

        static entity_id get_main_camera();
        static void set_main_camera(const entity_id e);

        static void draw_camera(entity_id id = get_main_camera(), glm::mat3 mat = glm::identity<glm::mat3>());

        void iterate(std::map<entity_id, entity>::iterator& it) override;
    };
}
