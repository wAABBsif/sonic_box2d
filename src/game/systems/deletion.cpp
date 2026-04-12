#include "deletion.hpp"
#include "game/entity.hpp"

using namespace sb2d::game::systems;

void deletion::iterate(std::map<entity_id, entity>::iterator& it)
{
    entity::get_all().erase(it);
    it--;
}

void deletion::init()
{
    deletion& self = get();
    self.tags |= entity::TAG_DELETION;

    add_system(&self);
}
