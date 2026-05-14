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
            bool is_active;

        public:
            source();
            source(const source& s);
            source (const source&& s);
            virtual ~source();

            void play(al_object buffer);
            void stop();
            void pause();

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
