#include "format.hpp"
#include "core/log.hpp"
#include "fstream"

using namespace sb2d::audio;

void format::load_wav(const std::string& path)
{
    char header_buffer[0x2C];
    stream = std::ifstream(path, std::ios::binary);
    stream.read(header_buffer, 0x2C);
    if (stream.eof())
    {
        LOG_WARNING(path + " is too short!");
        return;
    }

    if (std::string(header_buffer + 0x0, 4) != "RIFF"
            || std::string(header_buffer + 0x8, 4) != "WAVE"
            || std::string(header_buffer + 0xC, 4) != "fmt "
            || std::string(header_buffer + 0x24, 4) != "data")
    {
        return;
    }

    type = sb2d::audio::format::filetype::WAV;
    bits = *reinterpret_cast<uint16_t*>(header_buffer + 0x22);
    channels = *reinterpret_cast<uint16_t*>(header_buffer + 0x16);
    freq = *reinterpret_cast<uint32_t*>(header_buffer + 0x18);
    size = *reinterpret_cast<uint32_t*>(header_buffer + 0x28);
}

format::format(const std::string& path)
{
    if (path.ends_with(".wav"))
    {
       load_wav(path);
       return;
    }

    LOG_WARNING("Audio file '", path, "' not supported");
}

void format::read(char* buffer, uint32_t size)
{
    stream.read(buffer, size);
}

bool format::isValid()
{
    return type != filetype::NONE;
}
