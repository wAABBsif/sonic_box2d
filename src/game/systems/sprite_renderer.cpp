#include "sprite_renderer.hpp"
#include "core/log.hpp"
#include "game/components/sprite.hpp"
#include "game/components/transform.hpp"
#include "gfx/texture.hpp"
#include <algorithm>

using namespace sb2d::gfx;
using namespace sb2d::game::systems;

struct sprite_vertex
{
    glm::vec2 position;
    glm::vec2 texture_coords;
    sb2d::color tint;
    int32_t depth;
    int32_t texture_index;
};

struct sprite_quad
{
    sprite_vertex vertices[4];
    sprite_quad() = default;
    sprite_quad(const sb2d::game::components::sprite& sprite, const glm::mat3 local_to_world);
};

static std::array<sprite_quad, sprite_renderer::capacity> s_quads;
static size_t s_quad_count;
static std::vector<std::string> s_current_textures;

sprite_quad::sprite_quad(const sb2d::game::components::sprite& sprite, const glm::mat3 local_to_world)
{
    int texture_idx = 0;
    auto it = std::find(s_current_textures.begin(), s_current_textures.end(), sprite.texture);
    if (it == s_current_textures.end())
    {
        texture_idx = s_current_textures.size();
        s_current_textures.push_back(sprite.texture);
    }
    else
    {
        texture_idx = std::distance(s_current_textures.begin(), it);
    }

    if (texture_idx >= texture::slot_count)
        LOG_WARNING("Using slot beyond expected limit!");

    vertices[0] = {glm::vec2(-0.5f, +0.5f), glm::vec2(sprite.texture_coords[0].x, sprite.texture_coords[0].y), sprite.tint, sprite.depth, texture_idx};
    vertices[1] = {glm::vec2(-0.5f, -0.5f), glm::vec2(sprite.texture_coords[0].x, sprite.texture_coords[1].y), sprite.tint, sprite.depth, texture_idx};
    vertices[2] = {glm::vec2(+0.5f, -0.5f), glm::vec2(sprite.texture_coords[1].x, sprite.texture_coords[1].y), sprite.tint, sprite.depth, texture_idx};
    vertices[3] = {glm::vec2(+0.5f, +0.5f), glm::vec2(sprite.texture_coords[1].x, sprite.texture_coords[0].y), sprite.tint, sprite.depth, texture_idx};

    for (int i = 0; i < 4; i++)
    {
        glm::vec3 v = glm::vec3(vertices[i].position.x, vertices[i].position.y, 1);
        v = local_to_world * v;
        vertices[i].position = v;
    }
}

void sprite_renderer::iterate(std::map<entity_id, entity>::iterator& it)
{
    if (s_quad_count >= sprite_renderer::capacity)
    {
        LOG_WARNING("Sprite quad count exceeds capacity!");
        return;
    }

    components::transform& transform = *components::transform::get(it->first);
    components::sprite& sprite = *components::sprite::get(it->first);

    glm::mat3 local_to_world = transform.local_to_world();
    s_quads[s_quad_count] = sprite_quad(sprite, local_to_world);
    s_quad_count++;
}

void sprite_renderer::init()
{
    create_render_objects();
    bind_render_objects();

    set_shader("shaders/sprite.glsl");
    set_vertex_total_size(sizeof(sprite_vertex));
    s_current_textures.reserve(texture::slot_count);

    add_vertex_attribute_float(renderer_base::field_type::FLOAT_32, offsetof(sprite_vertex, position), 2, false);
    add_vertex_attribute_float(renderer_base::field_type::FLOAT_32, offsetof(sprite_vertex, texture_coords), 2, false);
    add_vertex_attribute_float(renderer_base::field_type::FLOAT_32, offsetof(sprite_vertex, tint), 4, false);
    add_vertex_attribute_float(renderer_base::field_type::INT_32, offsetof(sprite_vertex, depth), 1, true);
    add_vertex_attribute_int(renderer_base::field_type::INT_32, offsetof(sprite_vertex, texture_index), 2);

    create_vertex_data(capacity * 4, nullptr, true);

    uint16_t indices[capacity * 6];
    generate_quad_indices(indices, capacity);
    create_index_data(capacity * 6, indices, false);

    unbind_render_objects();
    
    sprite_renderer& self = get();
    self.components |= 1 << component_base::COMPONENT_TRANSFORM;
    self.components |= 1 << component_base::COMPONENT_SPRITE;
}

void sprite_renderer::terminate()
{
    set_shader();
    unbind_render_objects();
    destroy_render_objects();    
}

void sprite_renderer::draw()
{
    bind_render_objects();
    shader::set_current(get_shader());

    std::sort(s_quads.begin(), s_quads.end(), 
        [](const sprite_quad& a, const sprite_quad& b)
        {
            return a.vertices[0].depth < b.vertices[0].depth;
        }
    );

    for (int i = 0; i < s_current_textures.size(); i++)
    {
        auto& path = s_current_textures[i];
        auto t = texture::get(path);
        if (!t)
        {
            LOG_WARNING("Texture ", path, " not loaded!");
            continue;
        }

        get_shader().set_int("textures[" + std::to_string(i) + "]", i);
        texture::set_slot(*t, i);
    }

    write_vertex_data(0, s_quad_count * 4, s_quads.data());
    draw_elements(s_quad_count * 6);

    s_quad_count = 0;
    s_current_textures.clear();
}
