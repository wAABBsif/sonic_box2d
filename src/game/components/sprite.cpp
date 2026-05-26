#include "sprite.hpp"
#include "game/component.hpp"
#include "glm/fwd.hpp"
#include "imgui/imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

using namespace sb2d::game;
using namespace sb2d::game::components;
using namespace sb2d::gfx;

sprite::sprite(const std::string& texture, std::array<glm::ivec2, 2> texture_coords, float depth, color tint)
    : texture(texture), texture_coords(texture_coords), depth(depth), tint(tint) 
{}

constexpr component_base::type sprite::get_type()
{
    return type;
}

constexpr std::string sprite::get_name()
{
    return name;
}

void sprite::update_debug_inspector()
{
#if defined (IS_DEBUG)
    ImGui::InputText("Texture", &this->texture);
    ImGui::DragInt2("Texture Coords", reinterpret_cast<int*>(&texture_coords[0]), 1, 0, 65536);
    ImGui::DragInt2("", reinterpret_cast<int*>(&texture_coords[1]), 1, 0, 65536);
    ImGui::ColorEdit4("Tint", this->tint.data());
    ImGui::DragInt("Depth", &this->depth, 1, 0, 0);
    if (ImGui::Button("Remove"))
    {
        for (auto& c : get_all())
        {
            if (&c.second == this)
            {
                remove(c.first);
                return;
            }
        }
    }
#endif
}

sprite* sprite::add(entity_id id, const std::string &texture, std::array<glm::ivec2, 2> texture_coords, float depth)
{
    enable_component(id, type);
    return &get_all().insert({id, sprite(texture, texture_coords, depth)}).first->second;
}

void sprite::remove(entity_id id)
{
    disable_component(id, type);
    get_all().erase(id);
}
