#include "entity.hpp"
#include "core/log.hpp"
#include <cstddef>
#include <memory>
#include <vector>

using namespace sb2d::game;

constexpr size_t GAME_OBJECT_ALLOCATION_SIZE = 64;

static std::vector<std::shared_ptr<entity>> s_entities;

void entity::init()
{
    s_entities.reserve(GAME_OBJECT_ALLOCATION_SIZE);
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
        if ((*it)->get_tag(QUEUE_DELETION))
        {
            s_entities.erase(it);
            it--;
        }
    }
}

std::weak_ptr<entity> entity::create(std::string name, tag tags)
{
    return s_entities.emplace_back(std::make_shared<entity>(name, tags));
}

size_t entity::get_count()
{
    return s_entities.size();
}

std::vector<std::shared_ptr<entity>>& entity::get_all()
{
    return s_entities;
}

entity::entity(std::string name, tag tags)
    : name(name), tags(tags), components(std::vector<std::shared_ptr<component>>())
{}

void entity::set_tag(tag t, bool value)
{
    if (value)
        this->tags = (tag)(this->tags | t);
    else
        this->tags = (tag)(this->tags & ~t);
}

bool entity::get_tag(tag t)
{
    return this->tags & t;
}

void entity::queue_deletion()
{
    entity::set_tag(QUEUE_DELETION, true);
}
