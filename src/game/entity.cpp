#include "entity.hpp"
#include "core/log.hpp"
#include <cstddef>
#include <map>

using namespace sb2d::game;

entity::entity(const std::string& name)
    : name(name)
{}

entity::entity_id entity::get_unique_id()
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

void entity::update()
{
    for (auto it = s_entities.begin(); it != s_entities.end(); it++)
    {
        if ((it->second).get_tag(TAG_DELETION))
        {
            s_entities.erase(it);
            it--;
        }
    }
}

entity::entity_id entity::create(const std::string& name)
{
    entity_id id = get_unique_id();
    s_entities.insert({id, entity(name)});
    return id;
}

std::map<entity::entity_id, entity>& entity::get_all()
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
