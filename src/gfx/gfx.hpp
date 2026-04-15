#pragma once
#include "glm/glm.hpp"
#include <cstdint>

namespace sb2d::gfx
{
    using gl_object = uint32_t;

    void init();
    void terminate();

    void draw();
    void init_imgui();

    glm::ivec2 get_window_size();
}
