#include "component.hpp"
#include "entity.hpp"
#include "components/transform.hpp"
#include "components/sprite.hpp"
#include "game/components/audio_source.hpp"
#include "game/components/camera.hpp"

using namespace sb2d::game;

component_base* component_base::get(type type, entity_id id)
{
    switch (type)
    {
    case type::COMPONENT_TRANSFORM:
        return components::transform::get(id);
    case type::COMPONENT_SPRITE:
        return components::sprite::get(id);
    case type::COMPONENT_CAMERA:
        return components::camera::get(id);
    case type::COMPONENT_AUDIO_SOURCE:
        return components::audio_source::get(id);
    default:
        return nullptr;
    }
}

void component_base::enable_component(entity_id id, component_base::type type)
{
    entity *e = entity::get(id);
    component_mask mask = e->get_component_mask();
    mask |= 1 << type;
    e->set_component_mask(mask);
}

void component_base::disable_component(entity_id id, component_base::type type)
{
    entity *e = entity::get(id);
    component_mask mask = e->get_component_mask();
    mask &= ~(1 << type);
    e->set_component_mask(mask);
}
