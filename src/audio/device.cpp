#include "device.hpp"
#include "AL/alc.h"
#include "core/log.hpp"
#include <cstdlib>

using namespace sb2d::audio;

device::device()
{
    al_device = alcOpenDevice(nullptr);
    if (al_device == nullptr)
    {
        LOG_ERROR("Failed to open audio device");
        exit(EXIT_FAILURE);
    }

    al_context = alcCreateContext(al_device, nullptr);
    if (al_context == nullptr)
    {
        LOG_ERROR("Failed to create audio context");
        exit(EXIT_FAILURE);
    }

    alcMakeContextCurrent(al_context);
}

device::~device()
{
    alcDestroyContext(al_context);
    alcCloseDevice(al_device);
}
