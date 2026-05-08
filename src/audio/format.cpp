#include "format.hpp"
#include "core/log.hpp"
#include "fstream"

using namespace sb2d::audio;

void load_wav(format& result, const std::string& path)
{
    result.type = sb2d::audio::format::filetype::WAV;
    result.buffer = nullptr;

    char header_buffer[0x2C];
    std::ifstream file_stream = std::ifstream(path, std::ios::binary);
    file_stream.read(header_buffer, 0x2C);
    if (file_stream.eof())
    {
        LOG_WARNING(path + " is too short!");
        return;
    }

    if (std::string(header_buffer + 0x0, 4) != "RIFF"
            || std::string(header_buffer + 0x8, 4) != "WAVE"
            || std::string(header_buffer + 0xC, 4) != "fmt "
            || std::string(header_buffer + 0x24, 4) != "data")
    {
        LOG_WARNING(path, " could not be loaded");
        return;
    }

    result.bits = *reinterpret_cast<uint16_t*>(header_buffer + 0x22);
    result.channels = *reinterpret_cast<uint16_t*>(header_buffer + 0x16);
    result.freq = *reinterpret_cast<uint32_t*>(header_buffer + 0x18);
    result.size = *reinterpret_cast<uint32_t*>(header_buffer + 0x28);

    result.buffer = new char[result.size];
    file_stream.read(result.buffer, result.size);

    return;
}

format::format(const std::string& path)
{
    if (path.ends_with(".wav"))
    {
       load_wav(*this, path);
       return;
    }

    LOG_WARNING("Audio file '", path, "' not supported");
}

format::~format()
{
    delete buffer;
}

bool format::isValid()
{
    return buffer != nullptr;
}
