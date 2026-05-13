#include "clip.hpp"
#include "AL/al.h"
#include "audio/format.hpp"
#include "core/log.hpp"

using namespace sb2d::audio;

clip::clip(const std::string& path)
    : fmt(path)
{
    char* buffer = new char[fmt.size];
    fmt.read(buffer, fmt.size);

    ALenum al_format;
    if (fmt.channels == 1)
    {
        if (fmt.bits == 8)
            al_format = AL_FORMAT_MONO8;
        else if (fmt.bits == 16)
            al_format = AL_FORMAT_MONO16;
        else
        {
            LOG_WARNING("Incompatible bit count on '", path, "'");
            return;
        }
    }
    else if (fmt.channels == 2)
    {
        if (fmt.bits == 8)
            al_format = AL_FORMAT_STEREO8;
        else if (fmt.bits == 16)
            al_format = AL_FORMAT_STEREO16;
        else
        {
            LOG_WARNING("Incompatible bit count on '", path, "'");
            return;
        }
    }
    else
    {
        LOG_WARNING("Incompatible channel count on '", path, "'");
        return;
    }

    alGenBuffers(1, &al_id);
    alBufferData(al_id, al_format, buffer, fmt.size, fmt.freq);
}

clip::~clip()
{
    alDeleteBuffers(1, &al_id);
}

al_object clip::get_al_id()
{
    return al_id;
}
