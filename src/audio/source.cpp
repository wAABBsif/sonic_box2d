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

void source::pause()
{
    alSourcePause(al_id);
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

void source::set_pitch(const float value)
{
    alSourcef(al_id, AL_PITCH, value);
}

float source::get_pitch()
{
    float result;
    alGetSourcef(al_id, AL_PITCH, &result);
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

void source::set_position(const glm::vec3 value)
{
    alSource3f(al_id, AL_POSITION, value.x, value.y, value.z);
}

glm::vec3 source::get_position()
{
    glm::vec3 result;
    alGetSource3f(al_id, AL_POSITION, &result.x, &result.y, &result.z);
    return result;
}

void source::set_velocity(const glm::vec3 value)
{
    alSource3f(al_id, AL_VELOCITY, value.x, value.y, value.z);
}

glm::vec3 source::get_velocity()
{
    glm::vec3 result;
    alGetSource3f(al_id, AL_VELOCITY, &result.x, &result.y, &result.z);
    return result;
}
