#include "audio_source.hpp"
#include "audio/clip.hpp"
#include "core/log.hpp"
#include "game/component.hpp"
#include "imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

using namespace sb2d::game;
using namespace sb2d::game::components;
using namespace sb2d::audio;

audio_source::audio_source(const std::string& clip, float volume, float pitch, bool is_looping)
    : clip(clip), volume(volume), pitch(pitch), is_looping(is_looping)
{}

constexpr component_base::type audio_source::get_type()
{
    return COMPONENT_AUDIO_SOURCE;
}

constexpr std::string audio_source::get_name()
{
    return "Audio Source";
}

void audio_source::update_debug_inspector()
{
#if defined (IS_DEBUG)
    ImGui::InputText("Clip", &this->clip);
    ImGui::SliderFloat("Volume", &volume, 0, 2);
    ImGui::SliderFloat("Pitch", &pitch, 0, 2);
    ImGui::Checkbox("Is Looping", &is_looping);
    if (ImGui::Button("Play"))
    {
        play();
    }
    ImGui::SameLine();
    if (ImGui::Button("Pause"))
    {
        pause();
    }
    ImGui::SameLine();
    if (ImGui::Button("Stop"))
    {
        stop();
    }
#endif
}

audio_source* audio_source::add(entity_id id, const std::string& clip, float volume, float pitch, bool is_looping)
{
    enable_component(id, COMPONENT_AUDIO_SOURCE);
    return &get_all().insert({id, audio_source(clip, volume, pitch, is_looping)}).first->second;
}

void audio_source::remove(entity_id id)
{
    disable_component(id, COMPONENT_AUDIO_SOURCE);
    get_all().erase(id);
}

void audio_source::play()
{
    audio::clip* clip = audio::clip::get(this->clip);
    if (clip == nullptr)
    {
        LOG_WARNING("Clip '", this->clip, "' not loaded!");
        return;
    }

    source::set_volume(volume);
    source::set_pitch(pitch);
    source::play(clip->get_al_id());
}

void audio_source::pause()
{
    source::pause();
}

void audio_source::stop()
{
    source::stop();
}
