#pragma once
#include "component.hpp"

namespace sb2d::game
{
    using tag_mask = uint32_t;

    class entity
    {
    public:
        enum tag : uint8_t
        {
            TAG_DELETION,
            TAG_COUNT
        };

    private:
        static inline std::map<entity_id, entity> s_entities;
        static inline entity_id s_next_id;

        entity(const std::string& name);
        static entity_id get_unique_id();

    public:
        static void init();
        static void terminate();
        static void update();
        
        static entity_id create(const std::string& name = "");

        static entity* get(entity_id id);
        static std::map<entity_id, entity>& get_all();

    public:
        std::string name;

        tag_mask tags;
        component_mask components;

    public:
        void set_tag(tag t, bool value);
        bool get_tag(tag t);
        tag_mask get_tag_mask();

    public:
        bool has_component(component_base::type type);
        component_mask get_component_mask();
        void set_component_mask(component_mask mask);

        friend class component_base;
    };
}
