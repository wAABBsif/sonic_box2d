#include "objects_window.hpp"
#include "core/time.hpp"
#include "game/game_object.hpp"
#include "imgui.h"
#include <memory>

#if defined (IS_DEBUG)
static sb2d::game::game_object* selected_object;
#endif

void sb2d::debug_ui::objects_window::update()
{
#if defined (IS_DEBUG)
    ImGui::Begin("Objects");
    ImGui::BeginListBox("##Objects", ImGui::GetContentRegionAvail());
    for (auto& obj : game::game_object::get_all())
    {
        bool selected = ImGui::Selectable(obj->name.c_str(), selected_object == obj.get());
        if (selected)
            selected_object = obj.get();
    }
    ImGui::EndListBox();
    ImGui::End();
#endif
}
