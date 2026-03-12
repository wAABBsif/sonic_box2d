#include "sprite.hpp"
#include "core/transformations.hpp"
#include "game/components/transform.hpp"
#include "gfx/renderer.hpp"
#include "gfx/shader.hpp"
#include "gfx/texture.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/fwd.hpp"
#include <cstddef>
#include <memory>
#include "core/log.hpp"
#include "imgui/imgui.h"

using namespace sb2d::game::components;
using namespace sb2d::gfx;

struct sprite_vertex
{
    glm::vec2 position;
    glm::vec2 texture_coords;
    float depth;
    int texture_index;
};

static std::array<sprite_vertex, sprite::capacity * 4> s_vertices;
static size_t s_quad_count;

sprite::sprite(const std::shared_ptr<gfx::texture>& texture, std::array<glm::ivec2, 2> texture_coords, float depth)
    : texture(texture), texture_coords(texture_coords), depth(depth) 
{}

constexpr std::string sprite::get_name()
{
    return "Sprite";
}

void sprite::update_debug_inspector()
{
#if defined (IS_DEBUG)
    ImGui::Text("I'll do this later...");
#endif
}

void sprite::init()
{
    create_render_objects();
    bind_render_objects();
    set_vertex_total_size(sizeof(sprite_vertex));

    add_vertex_attribute_float(renderer_base::field_type::FLOAT_32, offsetof(sprite_vertex, position), 2, false);
    add_vertex_attribute_float(renderer_base::field_type::FLOAT_32, offsetof(sprite_vertex, texture_coords), 2, false);
    add_vertex_attribute_float(renderer_base::field_type::FLOAT_32, offsetof(sprite_vertex, depth), 1, false);
    add_vertex_attribute_int(renderer_base::field_type::INT_32, offsetof(sprite_vertex, position), 2);

    create_vertex_data(capacity * 4, nullptr, true);

    uint16_t indices[capacity * 6];
    generate_quad_indices(indices, capacity);
    create_index_data(capacity * 6, indices, false);

    set_shader(shader::get("shaders/sprite.glsl"));

    unbind_render_objects();
}

void sprite::terminate()
{
    unbind_render_objects();
    destroy_render_objects();
    set_shader(nullptr);
}

void sprite::draw()
{  
    bind_render_objects();
    auto s = get_shader().lock();
    shader::set_current(*s.get());
    write_vertex_data(0, s_quad_count * 4, s_vertices.data());
    draw_elements(s_quad_count * 6);
    s_quad_count = 0;
}

void sprite::create_quad(sb2d::game::components::transform trans)
{
    if (s_quad_count >= sprite::capacity)
    {
        LOG_WARNING("Sprite quad count exceeds capacity!");
        return;
    }

    int texture_idx = 0;

    s_vertices[s_quad_count * 4 + 0] = {glm::vec2(-0.5f, +0.5f), glm::vec2(this->texture_coords[0].x, this->texture_coords[0].y), this->depth, texture_idx};
    s_vertices[s_quad_count * 4 + 1] = {glm::vec2(-0.5f, -0.5f), glm::vec2(this->texture_coords[0].x, this->texture_coords[1].y), this->depth, texture_idx};
    s_vertices[s_quad_count * 4 + 2] = {glm::vec2(+0.5f, -0.5f), glm::vec2(this->texture_coords[1].x, this->texture_coords[1].y), this->depth, texture_idx};
    s_vertices[s_quad_count * 4 + 3] = {glm::vec2(+0.5f, +0.5f), glm::vec2(this->texture_coords[1].x, this->texture_coords[0].y), this->depth, texture_idx};

    const glm::mat3 mat = trans.local_to_world();
    for (int i = 0; i < 4; i++)
    {
        glm::vec3 v = glm::vec3(s_vertices[s_quad_count * 4 + i].position.x, s_vertices[s_quad_count * 4 + i].position.y, 1);
        v = mat * v;
        s_vertices[s_quad_count * 4 + i].position = v;
    }

    s_quad_count++;
}


