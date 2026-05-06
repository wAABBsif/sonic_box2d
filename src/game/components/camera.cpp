#include "camera.hpp"
#include "game/component.hpp"
#include "game/systems/camera_renderer.hpp"
#include "gfx/framebuffer.hpp"
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>

using namespace sb2d::game;
using namespace sb2d::game::components;
using namespace sb2d::gfx;

camera::camera(const glm::ivec2 texture_size, const color clear_color)
    : clear_color(clear_color), framebuffer(gfx::framebuffer(texture_size))
{
}

constexpr component_base::type camera::get_type()
{
    return COMPONENT_CAMERA;
}

constexpr std::string camera::get_name()
{
    return "Camera";
}

void camera::update_debug_inspector()
{
#if defined (IS_DEBUG)
    ImGui::ColorEdit4("Clear Color", this->clear_color.data());
    glm::ivec2 size = get_framebuffer().get_size();
    ImGui::DragInt2("Viewport Size", glm::value_ptr(size));
    get_framebuffer().resize(size);
#endif
}

framebuffer& camera::get_framebuffer()
{
    return framebuffer;
}

camera* camera::add(entity_id id, const glm::ivec2 texture_size, const color clear_color)
{
    enable_component(id, COMPONENT_CAMERA);
    camera* result = &get_all().insert({id, camera(texture_size, clear_color)}).first->second;
    if (camera::get(systems::camera_renderer::get_main_camera()) == nullptr)
    {
        systems::camera_renderer::set_main_camera(id);
    }
    return result;
}
