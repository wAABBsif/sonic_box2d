#pragma once
#include "game/components/transform.hpp"
#include "gfx/renderer.hpp"
#include "game/component.hpp"
#include "gfx/texture.hpp"
#include "glm/fwd.hpp"
#include <memory>

namespace sb2d::game::components
{
    class sprite : public gfx::renderer<sprite>, public component
    {
    public:
        std::string texture;
        std::array<glm::ivec2, 2> texture_coords;
        float depth;

        sprite(const std::string& texture, std::array<glm::ivec2, 2> texture_coords, float depth = 0);

        constexpr std::string get_name() override;
        void update_debug_inspector() override;

        static void init();
        static void terminate();
        static void draw();

        void create_quad(sb2d::game::components::transform trans);

        static constexpr int capacity = 1024;
    };
}
