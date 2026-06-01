#pragma once
#include "game/component.hpp"
#include "phys/body.hpp"

namespace sb2d::game::components
{
    class rigidbody : public component<rigidbody>, public phys::body
    {
    public:
        rigidbody(body_type type = body_type::STATIC_BODY, glm::vec2 position = glm::vec2(0, 0), float rotation = 0);

        constexpr type get_type() override;
        constexpr std::string get_name() override;
        
        void update_debug_inspector() override;

        static rigidbody* add(entity_id id, body_type body_type = body_type::STATIC_BODY);
        static void remove(entity_id id);

        static constexpr component::type type = COMPONENT_RIGIDBODY;
        static constexpr std::string name = "Rigidbody";
    };
}
