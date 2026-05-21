#include "entities_window.hpp"
#include "core/time.hpp"
#include "game/entity.hpp"
#include "imgui.h"
#include <memory>
#include <string>

using namespace sb2d::game;
using namespace sb2d::debug_ui;

static entity_id selected_entity;

void entities_window::update()
{
#if defined (IS_DEBUG)
    ImGui::Begin("Entities");
    ImGui::BeginListBox("##Entities", ImGui::GetContentRegionAvail());
    
    if (ImGui::Button("+"))
    {
        entity_id e = entity::create("Object");
        entity::get(e)->name = "Object " + std::to_string(e);
    }
    ImGui::SameLine();
    if (ImGui::Button("-"))
    {
        entity* e = entity::get(selected_entity);
        if (e != nullptr)
        {
            e->set_tag(entity::TAG_DELETION, true);
        }
    }
    for (auto& entity : game::entity::get_all())
    {
        bool selected = ImGui::Selectable(entity.second.name.c_str(), selected_entity == entity.first);
        if (selected)
            selected_entity = entity.first;
    }
    ImGui::EndListBox();
    ImGui::End();
#endif
}

entity_id entities_window::get_selection()
{
    return selected_entity;
}
