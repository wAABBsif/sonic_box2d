#include "game_object.hpp"
#include "core/log.hpp"
#include <cstddef>
#include <memory>
#include <vector>

constexpr size_t GAME_OBJECT_ALLOCATION_SIZE = 64;

static std::vector<std::unique_ptr<sb2d::game::game_object>> s_game_objects;

void sb2d::game::game_object::init()
{
    s_game_objects.reserve(GAME_OBJECT_ALLOCATION_SIZE);
    LOG_MESSAGE("Initialized game objects");
}

void sb2d::game::game_object::terminate()
{
    s_game_objects.clear();
    LOG_MESSAGE("Terminated game objects");
}

void sb2d::game::game_object::update()
{
    for (auto it = s_game_objects.begin(); it != s_game_objects.end(); it++)
    {
        if ((*it)->get_tag(QUEUE_DELETION))
        {
            s_game_objects.erase(it);
            it--;
        }
    }
}

sb2d::game::game_object& sb2d::game::game_object::create(std::string name, obj_tag tags)
{
    return *s_game_objects.emplace_back(std::make_unique<sb2d::game::game_object>(name, tags));
}

size_t sb2d::game::game_object::get_count()
{
    return s_game_objects.size();
}

std::vector<std::unique_ptr<sb2d::game::game_object>>& sb2d::game::game_object::get_all()
{
    return s_game_objects;
}

sb2d::game::game_object::game_object(std::string name, obj_tag tags)
    : name(name), tags(tags)
{}

void sb2d::game::game_object::set_tag(obj_tag t, bool value)
{
    if (value)
        this->tags = (obj_tag)(this->tags | t);
    else
        this->tags = (obj_tag)(this->tags & ~t);
}

bool sb2d::game::game_object::get_tag(obj_tag t)
{
    return this->tags & t;
}

void sb2d::game::game_object::queue_deletion()
{
    sb2d::game::game_object::set_tag(QUEUE_DELETION, true);
}
