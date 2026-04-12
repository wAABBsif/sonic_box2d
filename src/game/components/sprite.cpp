#include "sprite.hpp"
#include "core/transformations.hpp"
#include "game/component.hpp"
#include "game/components/transform.hpp"
#include "gfx/renderer.hpp"
#include "gfx/shader.hpp"
#include "gfx/texture.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/fwd.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include "core/log.hpp"
#include "imgui/imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

using namespace sb2d::game;
using namespace sb2d::game::components;
using namespace sb2d::gfx;

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
};

static std::array<sprite_quad, sprite::capacity> s_quads;
static size_t s_quad_count;
static std::vector<std::string> s_current_textures;

sprite::sprite(const std::string& texture, std::array<glm::ivec2, 2> texture_coords, float depth, color tint)
    : texture(texture), texture_coords(texture_coords), depth(depth), tint(tint) 
{}

constexpr component_base::type sprite::get_type()
{
    return COMPONENT_SPRITE;
}

constexpr std::string sprite::get_name()
{
    return "Sprite";
}

void sprite::update_debug_inspector()
{
#if defined (IS_DEBUG)
    ImGui::InputText("Texture", &this->texture);
    ImGui::DragInt2("Texture Coords", reinterpret_cast<int*>(&texture_coords[0]), 1, 0, 65536);
    ImGui::DragInt2("", reinterpret_cast<int*>(&texture_coords[1]), 1, 0, 65536);
    ImGui::ColorEdit4("Tint", this->tint.data());
    ImGui::DragInt("Depth", &this->depth, 1, 0, 0); 
#endif
}

sprite* sprite::add(entity_id id, const std::string &texture, std::array<glm::ivec2, 2> texture_coords, float depth)
{
    enable_component(id, COMPONENT_SPRITE);
    return &get_all().insert({id, sprite(texture, texture_coords, depth)}).first->second;
}

void sprite::remove(entity_id id)
{
    disable_component(id, COMPONENT_SPRITE);
    get_all().erase(id);
}

void sprite::init()
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
}

void sprite::terminate()
{
    set_shader();
    unbind_render_objects();
    destroy_render_objects();
}

void sprite::draw()
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

void sprite::create_quad(sb2d::game::components::transform& trans)
{
    if (s_quad_count >= sprite::capacity)
    {
        LOG_WARNING("Sprite quad count exceeds capacity!");
        return;
    }

    int texture_idx = 0;
    auto it = std::find(s_current_textures.begin(), s_current_textures.end(), this->texture);
    if (it == s_current_textures.end())
    {
        texture_idx = s_current_textures.size();
        s_current_textures.push_back(this->texture);
    }
    else
    {
        texture_idx = std::distance(s_current_textures.begin(), it);
    }

    if (texture_idx >= texture::slot_count)
        LOG_WARNING("Using slot beyond expected limit!");

    s_quads[s_quad_count].vertices[0] = {glm::vec2(-0.5f, +0.5f), glm::vec2(this->texture_coords[0].x, this->texture_coords[0].y), this->tint, this->depth, texture_idx};
    s_quads[s_quad_count].vertices[1] = {glm::vec2(-0.5f, -0.5f), glm::vec2(this->texture_coords[0].x, this->texture_coords[1].y), this->tint, this->depth, texture_idx};
    s_quads[s_quad_count].vertices[2] = {glm::vec2(+0.5f, -0.5f), glm::vec2(this->texture_coords[1].x, this->texture_coords[1].y), this->tint, this->depth, texture_idx};
    s_quads[s_quad_count].vertices[3] = {glm::vec2(+0.5f, +0.5f), glm::vec2(this->texture_coords[1].x, this->texture_coords[0].y), this->tint, this->depth, texture_idx};

    const glm::mat3 mat = trans.local_to_world();
    for (int i = 0; i < 4; i++)
    {
        glm::vec3 v = glm::vec3(s_quads[s_quad_count].vertices[i].position.x, s_quads[s_quad_count].vertices[i].position.y, 1);
        v = mat * v;
        s_quads[s_quad_count].vertices[i].position = v;
    }

    s_quad_count++;
}


