#include "system.hpp"
#include <vector>

#include "game/systems/sprite_renderer.hpp"
#include "game/systems/camera_manager.hpp"
#include "game/systems/deletion.hpp"

using namespace sb2d::game;

static std::vector<system_base*> s_systems;

void system_base::init()
{
    systems::sprite_renderer::init();
    systems::camera_manager::init();
    systems::deletion::init();

    add_system(&systems::sprite_renderer::get());
    add_system(&systems::camera_manager::get());
    add_system(&systems::deletion::get());
}

void system_base::terminate()
{
    systems::sprite_renderer::terminate();
}

void system_base::update()
{
    for (auto s : s_systems)
    {
        std::map<entity_id, entity>& entities = entity::get_all();
        for (auto it = entities.begin(); it != entities.end(); ++it)
        {
            if ((it->second.get_component_mask() & s->components) != s->components)
                continue;

            if ((it->second.get_tag_mask() & s->tags) != s->tags)
                continue;

            s->iterate(it); 
            if (it == entities.end())
                break;
        }
    }
}

void system_base::add_system(system_base* system)
{
    s_systems.push_back(system);
}
