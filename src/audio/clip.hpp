#pragma once
#include "audio.hpp"
#include "core/asset.hpp"

namespace sb2d::audio
{
    class clip : public asset<clip>
    {
        private:
            al_object al_id;

        public:
            clip(const std::string& path);
            ~clip();
    };
}
