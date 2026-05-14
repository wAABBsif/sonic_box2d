#pragma once
#include "game/component.hpp"
#include "audio/source.hpp"

namespace sb2d::game::components
{
    class audio_source : public component<audio_source>, audio::source
    {
    public:
        std::string clip;
        float volume;
        float pitch;
        bool is_looping;
    
        audio_source(const std::string& clip, float volume = 1, float pitch = 1, bool is_looping = false);

        constexpr type get_type() override;
        constexpr std::string get_name() override;
        void update_debug_inspector() override;

        static audio_source* add(entity_id id, const std::string& clip, float volume = 1, float pitch = 1, bool is_looping = false);
        static void remove(entity_id id);

        void play();
        void pause();
        void stop();
    };
}
