#include "components_window.hpp"
#include "entities_window.hpp"
#include "core/time.hpp"
#include "game/entity.hpp"
#include "imgui.h"
#include <memory>
#include "game/component.hpp"

using namespace sb2d::game;
using namespace sb2d::debug_ui;

void components_window::update()
{
#if defined (IS_DEBUG)
    ImGui::Begin("Components");
    entity_id id = entities_window::get_selection();
    entity* entity = entity::get(id);
    if (!entity)
    {
        ImGui::Text("No entity selected...");
        ImGui::End();
        return;
    }

    for (int i = 0; i < component_base::COMPONENT_COUNT; i++)
    {
        if (!entity->has_component((component_base::type)i))
            continue;
        component_base* component = component_base::get((component_base::type)i, id);
        if (ImGui::CollapsingHeader(component->get_name().c_str()))
        {
            component->update_debug_inspector();
        }
    }
    ImGui::End();
#endif
}
