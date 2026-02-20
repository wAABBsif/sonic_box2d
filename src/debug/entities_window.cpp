#include "entities_window.hpp"
#include "core/time.hpp"
#include "game/entity.hpp"
#include "imgui.h"
#include <memory>

#if defined (IS_DEBUG)
static sb2d::game::entity* selected_entity;
#endif

void sb2d::debug_ui::entities_window::update()
{
#if defined (IS_DEBUG)
    ImGui::Begin("Entities");
    ImGui::BeginListBox("##Entities", ImGui::GetContentRegionAvail());
    for (auto& obj : game::entity::get_all())
    {
        bool selected = ImGui::Selectable(obj->name.c_str(), selected_entity == obj.get());
        if (selected)
            selected_entity = obj.get();
    }
    ImGui::EndListBox();
    ImGui::End();
#endif
}
