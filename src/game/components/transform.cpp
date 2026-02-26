#include "transform.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/matrix_float3x3.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "imgui.h"
#include <memory>
#include "core/transformations.hpp"

using namespace sb2d::game;

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

glm::mat3 sb2d::game::components::transform::local_to_world()
{
    glm::mat3 result = glm::identity<glm::mat3>();
    result = transformations::translate(result, this->position);
    result = transformations::rotate(result, this->rotation);
    result = transformations::scale(result, this->scale);
    return result;
}

glm::mat3 sb2d::game::components::transform::world_to_local()
{
    glm::mat3 result = glm::identity<glm::mat3>();
    result = transformations::scale(result, glm::vec2(1 / this->scale.x, 1 / this->scale.y));
    result = transformations::rotate(result, -this->rotation);
    result = transformations::translate(result, -this->position);
    return result;
}
