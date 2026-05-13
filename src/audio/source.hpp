#pragma once
#include "audio.hpp"
#include <string>
#include "glm/glm.hpp"

namespace sb2d::audio
{
    class source
    {
        private:
            al_object al_id;
            std::string clip;

        public:
            source();
            virtual ~source();

            void play();
            void stop();
            void pause();

            void set_clip(const std::string& path);
            std::string get_clip();

            void set_volume(const float value);
            float get_volume();

            void set_pitch(const float value);
            float get_pitch();

            void set_looping(const bool value);
            bool get_looping();

            void set_position(const glm::vec3 value);
            glm::vec3 get_position();

            void set_velocity(const glm::vec3 value);
            glm::vec3 get_velocity();
    };
}
