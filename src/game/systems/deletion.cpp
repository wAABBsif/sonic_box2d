#include "deletion.hpp"
#include "game/entity.hpp"

using namespace sb2d::game::systems;

void deletion::iterate(std::map<entity_id, entity>::iterator& it)
{
    //it = entity::get_all().erase(it);
}

void deletion::init()
{
    deletion& self = get();
    self.tags |= 1 << entity::TAG_DELETION;
}
