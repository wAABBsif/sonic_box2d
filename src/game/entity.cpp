#include "entity.hpp"
#include "core/log.hpp"
#include "game/component.hpp"
#include <cstddef>
#include <map>

using namespace sb2d::game;

entity::entity(const std::string& name)
    : name(name), tags(0), components(0)
{}

entity_id entity::get_unique_id()
{
    s_next_id++;
    return s_next_id; 
}

void entity::init()
{
    LOG_MESSAGE("Initialized entities");
}

void entity::terminate()
{
    s_entities.clear();
    LOG_MESSAGE("Terminated entities");
}

entity_id entity::create(const std::string& name)
{
    entity_id id = get_unique_id();
    s_entities.insert({id, entity(name)});
    return id;
}

entity* entity::get(entity_id id)
{
    auto it = s_entities.find(id);
    if (it == s_entities.end())
        return nullptr;

    return &it->second;
}

std::map<entity_id, entity>& entity::get_all()
{
    return s_entities;
}

void entity::set_tag(tag t, bool value)
{
    if (value)
        this->tags |= 1 << t;
    else
        this->tags &= ~(1 << t);
}

bool entity::get_tag(tag t)
{
    return this->tags & (1 << t);
}

tag_mask entity::get_tag_mask()
{
    return this->tags;
}

bool entity::has_component(component_base::type type)
{
    return this->components & (1 << type);
}

component_mask entity::get_component_mask()
{
    return this->components;
}

void entity::set_component_mask(component_mask mask)
{
    this->components = mask;
}
