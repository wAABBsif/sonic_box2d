#pragma once
#include "glm/glm.hpp"
#include <cstdint>
#include "core/color.hpp"
#include "framebuffer.hpp"

namespace sb2d::gfx
{
    using gl_object = uint32_t;

    void init();
    void init_imgui();
    void terminate();

    void render_to_framebuffer(const framebuffer& fb, const color clear_color, const glm::mat3 world_to_camera);
    void render_to_screen();

    glm::ivec2 get_window_size();
}
