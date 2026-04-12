#include "sprite_manager.hpp"
#include "game/components/sprite.hpp"
#include "game/components/transform.hpp"
#include "game/system.hpp"

using namespace sb2d::game::systems;

void sprite_manager::iterate(std::map<entity_id, entity>::iterator& it)
{
    components::transform& transform = *components::transform::get(it->first);
    components::sprite::get(it->first)->create_quad(transform);
}

void sprite_manager::init()
{
    sprite_manager& self = get();
    self.components |= component_base::COMPONENT_TRANSFORM;
    self.components |= component_base::COMPONENT_SPRITE;

    system_base::add_system(reinterpret_cast<system_base*>(&self));
}
