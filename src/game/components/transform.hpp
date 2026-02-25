#pragma once
#include "game/component.hpp"
#include "glm/ext/vector_float2.hpp"
#include <glm/glm.hpp>
#include <string>

namespace sb2d::game::components
{
    class transform : public component
    {
    public:
        glm::vec2 position;
        float rotation;
        glm::vec2 scale;

        transform(glm::vec2 position = glm::vec2(0, 0), float rotation = 0, glm::vec2 scale = glm::vec2(1, 1));

        constexpr std::string get_name() override;
        void update_debug_inspector() override;

        glm::mat3 local_to_world();
        glm::mat3 world_to_local();
    };
}
