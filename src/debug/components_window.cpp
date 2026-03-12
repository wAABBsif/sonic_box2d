#include "components_window.hpp"
#include "entities_window.hpp"
#include "core/time.hpp"
#include "game/entity.hpp"
#include "imgui.h"
#include <memory>

using namespace sb2d::game;
using namespace sb2d::debug_ui;

void components_window::update()
{
#if defined (IS_DEBUG)
    ImGui::Begin("Components");
//    auto entity = entities_window::get_selection().lock();
//    if (!entity)
//    {
//        ImGui::Text("No entity selected...");
//        ImGui::End();
//        return;
//    }
//    for (auto component : entity->components)
//    {
//        ImGui::PushID(component.get());
//        if (ImGui::CollapsingHeader(component->get_name().c_str()))
//        {
//            component->update_debug_inspector();
//        }
//        ImGui::PopID();
//    }
    ImGui::End();
#endif
}
