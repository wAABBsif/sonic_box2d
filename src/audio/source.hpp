#pragma once
#include "audio.hpp"
#include <string>

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

            void set_clip(const std::string& path);
            std::string get_clip();

            void set_volume(const float value);
            float get_volume();

            void set_looping(const bool value);
            bool get_looping(); 
    };
}
