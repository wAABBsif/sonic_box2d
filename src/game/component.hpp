#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <map>

namespace sb2d::game
{
    class entity;

    using component_mask = uint32_t;
    using entity_id = size_t;

    class component_base
    {
    public:
        enum type : uint8_t
        {
            COMPONENT_TRANSFORM,
            COMPONENT_SPRITE,
            COMPONENT_CAMERA,
            COMPONENT_COUNT
        };

        virtual constexpr component_base::type get_type() = 0;
        virtual constexpr std::string get_name() = 0;
        virtual void update_debug_inspector() = 0;

        static component_base* get(type type, entity_id id);

        friend class sb2d::game::entity;

    protected:
        static void enable_component(entity_id id, component_base::type type);
        static void disable_component(entity_id id, component_base::type type);
    };

    template <typename derived>
    class component : public component_base
    {
        static inline std::map<entity_id, derived> s_elements;

    protected:
        static inline std::map<entity_id, derived>& get_all()
        {
            return s_elements;
        }

    public:
        static derived* get(entity_id id)
        {
            auto it = s_elements.find(id);
            if (it == s_elements.end())
                return nullptr;

            return &it->second;
        }
    };
}
