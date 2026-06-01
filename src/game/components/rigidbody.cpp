#include "rigidbody.hpp"
#include "game/component.hpp"
#include "game/components/transform.hpp"
#include "phys/body.hpp"
#include "imgui/imgui.h"
#include "phys/collision_shape.hpp"
#include <string>

using namespace sb2d::game;
using namespace sb2d::game::components;
using namespace sb2d::phys;

rigidbody::rigidbody(body_type type, const glm::vec2 position, const float rotation)
    : body(type, position, rotation)
{}

constexpr component_base::type rigidbody::get_type()
{
    return type;
}

constexpr std::string rigidbody::get_name()
{
    return name;
}

void rigidbody::update_debug_inspector()
{
    is_active = true;
#if defined (IS_DEBUG)
    if (ImGui::BeginCombo("Type", get_body_type_as_string().c_str()))
    {
        if (ImGui::Selectable(get_body_type_as_string(body_type::STATIC_BODY).c_str()))
            set_body_type(body_type::STATIC_BODY);
        if (ImGui::Selectable(get_body_type_as_string(body_type::KINEMATIC_BODY).c_str()))
            set_body_type(body_type::KINEMATIC_BODY);
        if (ImGui::Selectable(get_body_type_as_string(body_type::DYNAMIC_BODY).c_str()))
            set_body_type(body_type::DYNAMIC_BODY);
        ImGui::EndCombo();
    }

    glm::vec2 velocity = get_velocity();
    if (ImGui::DragFloat2("Velocity", reinterpret_cast<float*>(&velocity[0])))
        set_velocity(velocity);

    float angular_velocity = get_angular_velocity();
    if (ImGui::DragFloat("Angular Velocity", &angular_velocity))
        set_angular_velocity(angular_velocity);

    collision_shape* shapes = new collision_shape[get_shape_count()];
    get_shapes(shapes);
    collision_shape* old_shapes = (collision_shape*)memcpy(new collision_shape[get_shape_count()], shapes, sizeof(collision_shape) * get_shape_count());

    for (int i = 0; i < get_shape_count(); i++)
    {
        if (ImGui::CollapsingHeader((std::string("Shape ") + std::to_string(i)).c_str()))
        {
            ImGui::PushID(i);

            switch (shapes[i].type)
            {
                case collision_shape::shape_type::BOX:
                    ImGui::Text("Box");
                    ImGui::DragFloat2("Center", reinterpret_cast<float*>(&shapes[i].box.center[0]));
                    ImGui::DragFloat2("Radius", reinterpret_cast<float*>(&shapes[i].box.radius[0]));
                    break;
                case collision_shape::shape_type::CIRCLE:
                    ImGui::Text("Circle");
                    ImGui::DragFloat2("Center", reinterpret_cast<float*>(&shapes[i].circle.center[0]));
                    ImGui::DragFloat("Radius", &shapes[i].circle.radius);
                    break;
                case collision_shape::shape_type::CAPSULE:
                    ImGui::Text("Capsule");
                    ImGui::DragFloat2("Center 1", reinterpret_cast<float*>(&shapes[i].capsule.center1[0]));
                    ImGui::DragFloat2("Center 2", reinterpret_cast<float*>(&shapes[i].capsule.center2[0]));
                    ImGui::DragFloat("Radius", &shapes[i].capsule.radius);
                    break;
                default:
                    break;
            }

            if (memcmp(old_shapes + i, shapes + i, sizeof(collision_shape) * get_shape_count()) != 0)
            {
                set_shape(shapes[i], i);
            }

            if (ImGui::Button("Remove"))
                remove_shape(i);
        
            ImGui::PopID();
        }
    }

    delete[] shapes;
    delete[] old_shapes;

    if (ImGui::BeginCombo("Add Shape", "Select type..."))
    {
        if (ImGui::Selectable("Box"))
            add_shape(collision_shape(1, 0, 0, (collision_shape::box_def){glm::vec2(0, 0), glm::vec2(0.5f, 0.5f)}));
        else if (ImGui::Selectable("Circle"))
            add_shape(collision_shape(1, 0, 0, (collision_shape::circle_def){glm::vec2(0, 0), 0.5f}));
        else if (ImGui::Selectable("Capsule"))
            add_shape(collision_shape(1, 0, 0, (collision_shape::capsule_def){glm::vec2(0, -0.5f), glm::vec2(0, 0.5f), 0.5f}));
        ImGui::EndCombo();
    }
#endif
}

rigidbody* rigidbody::add(entity_id id, body_type body_type)
{
    components::transform& transform = *components::transform::get(id);
    enable_component(id, type);
    return &get_all().insert({id, rigidbody(body_type, transform.position, transform.rotation)}).first->second;
}

void rigidbody::remove(entity_id id)
{
    disable_component(id, type);
    get_all().erase(id);
}
