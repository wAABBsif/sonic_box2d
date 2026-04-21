#pragma once
#include "core/singleton.hpp"
#include "game/component.hpp"
#include "game/entity.hpp"

namespace sb2d::game
{
    struct system_base
    {
        static void init();
        static void terminate();
        static void update();
        static void add_system(system_base* system);
    
        component_mask components;
        tag_mask tags;
        virtual void iterate(std::map<entity_id, entity>::iterator& it) = 0;
    };

    template <typename derived>
    struct system : system_base, public singleton<derived>
    {

    };
}
