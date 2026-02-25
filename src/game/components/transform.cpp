#include "transform.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "imgui.h"
#include <memory>

sb2d::game::components::transform::transform(glm::vec2 position, float rotation, glm::vec2 scale)
    : position(position), rotation(rotation), scale(scale)
{}

constexpr std::string sb2d::game::components::transform::get_name()
{
    return "Transform";
}

void sb2d::game::components::transform::update_debug_inspector()
{
    ImGui::DragFloat2("Position", reinterpret_cast<float*>(&this->position), 0.1f);
    ImGui::DragFloat("Rotation", &this->rotation, 0.01f);
    ImGui::DragFloat2("Scale", reinterpret_cast<float*>(&this->scale), 0.01f);
}

glm::mat4 sb2d::game::components::transform::local_to_world()
{
    glm::mat4 result = glm::identity<glm::mat4>();
    result = glm::translate(result, glm::vec3(this->position.x, this->position.y, 0));
    result = glm::rotate(result, this->rotation, glm::vec3(0, 0, 1));
    result = glm::scale(result, glm::vec3(this->scale.x, this->scale.y, 1));
    return result;
}

glm::mat4 sb2d::game::components::transform::world_to_local()
{
    glm::mat4 result = glm::identity<glm::mat4>();
    result = glm::scale(result, glm::vec3(1 / this->scale.x, 1 / this->scale.y, 1));
    result = glm::rotate(result, -this->rotation, glm::vec3(0, 0, 1));
    result = glm::translate(result, glm::vec3(-this->position.x, -this->position.y, 0));
    return result;
}
