#pragma once
#include "glm/glm.hpp"
#include <cstdint>
#include "core/color.hpp"
#include "framebuffer.hpp"

namespace sb2d::gfx
{
    class window
    {
    public:
        window() = default;
        virtual ~window() = default;

        void render_to_framebuffer(framebuffer& fb, const color clear_color, const glm::mat3 world_to_camera);
        void render_to_screen();
        
        virtual void swap_buffers() = 0;

        virtual glm::ivec2 get_size() = 0;
        
        virtual void init_imgui() = 0;
    };
}
