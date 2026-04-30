#include "camera_renderer.hpp"
#include "game/component.hpp"
#include "game/components/transform.hpp"
#include "game/components/camera.hpp"
#include "game/game.hpp"
#include "gfx/renderer.hpp"
#include "gfx/shader.hpp"
#include <cstddef>

using namespace sb2d;
using namespace sb2d::gfx;
using namespace sb2d::game::systems;

struct camera_vertex
{
    glm::vec2 position;
    glm::vec2 texture_coords;
};

void camera_renderer::iterate(std::map<entity_id, entity>::iterator& it)
{
    window& win = game::get_main_window();
    components::transform& transform = *components::transform::get(it->first);
    components::camera& camera = *components::camera::get(it->first);

    win.render_to_framebuffer(camera.get_framebuffer(), camera.clear_color, transform.world_to_local());
}

void camera_renderer::init()
{
    create_render_objects();
    bind_render_objects();

    set_shader("shaders/camera.glsl");
    set_vertex_total_size(sizeof(camera_vertex));

    add_vertex_attribute_float(renderer_base::field_type::FLOAT_32, offsetof(camera_vertex, position), 2, false);
    add_vertex_attribute_float(renderer_base::field_type::FLOAT_32, offsetof(camera_vertex, texture_coords), 2, false);

    camera_vertex vertices[4] =
    {
        {{-1, 1}, {0, 1}},
        {{-1, -1}, {0, 0}},
        {{1, -1}, {1, 0}},
        {{1, 1}, {1, 1}}
    };
    create_vertex_data(4, vertices, false);

    uint16_t indices[6];
    generate_quad_indices(indices, 1);
    create_index_data(6, indices, false);

    unbind_render_objects();

    camera_renderer& self = get();
    self.components |= 1 << component_base::COMPONENT_TRANSFORM;
    self.components |= 1 << component_base::COMPONENT_CAMERA;
}

void camera_renderer::terminate()
{
    set_shader();
    unbind_render_objects();
    destroy_render_objects();
}

void camera_renderer::draw_camera(components::camera &cam, glm::mat3 mat)
{
    bind_render_objects();
    shader::set_current(get_shader());

    framebuffer::set_texture_slot(cam.get_framebuffer(), 1);
    get_shader().set_int("tex", 1);
    get_shader().set_mat3("mat", mat);

    draw_elements(6);
}
