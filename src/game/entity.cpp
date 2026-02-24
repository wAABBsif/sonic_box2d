#include "entity.hpp"
#include "core/log.hpp"
#include <cstddef>
#include <memory>
#include <vector>

constexpr size_t GAME_OBJECT_ALLOCATION_SIZE = 64;

static std::vector<std::shared_ptr<sb2d::game::entity>> s_entities;

void sb2d::game::entity::init()
{
    s_entities.reserve(GAME_OBJECT_ALLOCATION_SIZE);
    LOG_MESSAGE("Initialized entities");
}

void sb2d::game::entity::terminate()
{
    s_entities.clear();
    LOG_MESSAGE("Terminated entities");
}

void sb2d::game::entity::update()
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

sb2d::game::entity& sb2d::game::entity::create(std::string name, tag tags)
{
    return *s_entities.emplace_back(std::make_unique<sb2d::game::entity>(name, tags));
}

size_t sb2d::game::entity::get_count()
{
    return s_entities.size();
}

std::vector<std::shared_ptr<sb2d::game::entity>>& sb2d::game::entity::get_all()
{
    return s_entities;
}

sb2d::game::entity::entity(std::string name, tag tags)
    : name(name), tags(tags)
{}

void sb2d::game::entity::set_tag(tag t, bool value)
{
    if (value)
        this->tags = (tag)(this->tags | t);
    else
        this->tags = (tag)(this->tags & ~t);
}

bool sb2d::game::entity::get_tag(tag t)
{
    return this->tags & t;
}

void sb2d::game::entity::queue_deletion()
{
    sb2d::game::entity::set_tag(QUEUE_DELETION, true);
}
