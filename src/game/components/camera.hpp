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

        private:
            static constexpr type s_get_type();
            static constexpr std::string s_get_name();

        public:
            constexpr type get_type() override;
            constexpr std::string get_name() override;

            void update_debug_inspector() override;

            gfx::framebuffer& get_framebuffer();

            static camera* add(entity_id id, const glm::ivec2 texture_size, const color clear_color);
            static void remove(entity_id id);
    };
}
