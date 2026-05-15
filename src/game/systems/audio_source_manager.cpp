#include "audio_source_manager.hpp"
#include "game/component.hpp"
#include "game/components/audio_source.hpp"
#include "game/components/transform.hpp"

using namespace sb2d::audio;
using namespace sb2d::game::systems;

void audio_source_manager::iterate(std::map<entity_id, entity>::iterator& it)
{
    components::transform* transform = components::transform::get(it->first);
    components::audio_source& source = *components::audio_source::get(it->first);

    source.set_volume(source.volume);
    source.set_pitch(source.pitch);
    source.set_looping(source.is_looping);

    if (transform != nullptr)
    {
        source.set_position(glm::vec3(transform->position.x, transform->position.y, 0));
    }
}

void audio_source_manager::init()
{
    audio_source_manager& self = get();
    self.components |= 1 << component_base::COMPONENT_AUDIO_SOURCE;
}
