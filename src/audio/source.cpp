#include "source.hpp"
#include "AL/al.h"
#include "core/log.hpp"
#include "clip.hpp"

using namespace sb2d::audio;

source::source()
{
    alGenSources(1, &al_id);
}

source::~source()
{
    alDeleteSources(1, &al_id);
}

void source::play()
{
    auto c = clip::get(clip);
    if (!c)
    {
        LOG_WARNING("Clip ", clip, " not loaded!");
        return;
    }

    alSourcei(al_id, AL_BUFFER, c->get_al_id());
    alSourcePlay(al_id);
}

void source::stop()
{
    alSourceStop(al_id);
}

void source::set_clip(const std::string& path)
{
    this->clip = path;
}

std::string source::get_clip()
{
    return this->clip;
}

void source::set_volume(const float value)
{
    alSourcef(al_id, AL_GAIN, value);
}

float source::get_volume()
{
    float result;
    alGetSourcef(al_id, AL_GAIN, &result);
    return result;
}

void source::set_looping(const bool value)
{
    alSourcei(al_id, AL_LOOPING, value);
}

bool source::get_looping()
{
    int result;
    alGetSourcei(al_id, AL_LOOPING, &result);
    return (bool)result;
}
