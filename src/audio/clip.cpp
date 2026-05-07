#include "clip.hpp"
#include "AL/al.h"

using namespace sb2d::audio;

clip::clip(const std::string& path)
{
    ALenum format;
    void* buffer;
    uint32_t size;
    uint32_t freq;

    alGenBuffers(1, &al_id);
    alBufferData(al_id, format, buffer, size, freq);
}

clip::~clip()
{
    alDeleteBuffers(1, &al_id);
}
