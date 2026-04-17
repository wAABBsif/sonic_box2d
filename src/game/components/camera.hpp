#pragma once
#include "game/component.hpp"
#include "gfx/framebuffer.hpp"
#include "core/color.hpp"
#include "glm/fwd.hpp"

namespace sb2d::game::components
{
    class camera : public component<camera>
    {
        protected:
            gfx::framebuffer framebuffer;

        public:
            color clear_color;

            camera(const glm::ivec2 texture_size, const color clear_color);

            gfx::framebuffer get_framebuffer();
    };
}
