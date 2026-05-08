#include "clip.hpp"
#include "AL/al.h"
#include "audio/format.hpp"
#include "core/log.hpp"

using namespace sb2d::audio;

clip::clip(const std::string& path)
{
    format file_format = format(path);

    ALenum al_format;
    if (file_format.channels == 1)
    {
        if (file_format.bits == 8)
            al_format = AL_FORMAT_MONO8;
        else if (file_format.bits == 16)
            al_format = AL_FORMAT_MONO16;
        else
        {
            LOG_WARNING("Incompatible bit count on '", path, "'");
            return;
        }
    }
    else if (file_format.channels == 2)
    {
        if (file_format.bits == 8)
            al_format = AL_FORMAT_STEREO8;
        else if (file_format.bits == 16)
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
    alBufferData(al_id, al_format, file_format.buffer, file_format.size, file_format.freq);
}

clip::~clip()
{
    alDeleteBuffers(1, &al_id);
}
