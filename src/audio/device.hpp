#pragma once
#include "audio.hpp"
#include "AL/alc.h"

namespace sb2d::audio
{
    class device
    {
    private:
        ALCdevice* al_device;
        ALCcontext* al_context;
    public:
        device();
        ~device();
    };
}
