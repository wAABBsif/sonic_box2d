#include "source.hpp"
#include "AL/al.h"
#include "core/log.hpp"
#include "clip.hpp"

using namespace sb2d::audio;

source::source()
    : is_active(false)
{
    alGenSources(1, &al_id);
}

source::source(const source& s)
    : al_id(s.al_id), is_active(false)
{}

source::source(const source&& s)
    : al_id(s.al_id), is_active(false)
{}

source::~source()
{
    if (is_active)
        alDeleteSources(1, &al_id);
}

void source::play(al_object buffer)
{
    alSourcei(al_id, AL_BUFFER, buffer);
    alSourcePlay(al_id);
    is_active = true;
}

void source::stop()
{
    alSourceStop(al_id);
}

void source::pause()
{
    alSourcePause(al_id);
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
