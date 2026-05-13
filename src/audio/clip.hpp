#pragma once
#include "audio.hpp"
#include "audio/format.hpp"
#include "core/asset.hpp"

namespace sb2d::audio
{
    class clip : public asset<clip>
    {
    private:
        al_object al_id;

    public:
        format fmt;

        clip(const std::string& path);
        ~clip();

        al_object get_al_id();
    };
}
