#include "entities_window.hpp"
#include "core/time.hpp"
#include "game/entity.hpp"
#include "imgui.h"
#include <memory>

using namespace sb2d::game;
using namespace sb2d::debug_ui;

#if defined (IS_DEBUG)
static std::weak_ptr<sb2d::game::entity> selected_entity;
#endif

void entities_window::update()
{
#if defined (IS_DEBUG)
    ImGui::Begin("Entities");
    ImGui::BeginListBox("##Entities", ImGui::GetContentRegionAvail());
    for (auto& obj : game::entity::get_all())
    {
        bool selected = ImGui::Selectable(obj->name.c_str(), selected_entity.lock() == obj);
        if (selected)
            selected_entity = obj;
    }
    ImGui::EndListBox();
    ImGui::End();
#endif
}

std::weak_ptr<entity> entities_window::get_selection()
{
    return selected_entity;
}
