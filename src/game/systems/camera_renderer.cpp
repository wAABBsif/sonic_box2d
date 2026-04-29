#include "camera_renderer.hpp"
#include "game/component.hpp"
#include "game/components/transform.hpp"
#include "game/components/camera.hpp"
#include "game/game.hpp"

using namespace sb2d;
using namespace sb2d::gfx;
using namespace sb2d::game::systems;

void camera_renderer::iterate(std::map<entity_id, entity>::iterator& it)
{
    window& win = game::get_main_window();
    components::transform& transform = *components::transform::get(it->first);
    components::camera& camera = *components::camera::get(it->first);

    win.render_to_framebuffer(camera.get_framebuffer(), camera.clear_color, transform.world_to_local());
}

void camera_renderer::init()
{
    camera_renderer& self = get();
    self.components |= 1 << component_base::COMPONENT_TRANSFORM;
    self.components |= 1 << component_base::COMPONENT_CAMERA;
}
