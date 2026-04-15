#pragma once
#include "glm/glm.hpp"

namespace sb2d::gfx
{
    void init();
    void terminate();

    void draw();
    void init_imgui();

    glm::ivec2 get_window_size();
}
