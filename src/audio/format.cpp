#include "format.hpp"
#include "core/log.hpp"
#include "fstream"
#include <cstdint>
#include <iosfwd>

using namespace sb2d::audio;

void format::load_wav(const std::string& path)
{
    struct riff_master_header
    {
        char riff_identifier[4];
        uint32_t size;
        char format_identifier[4];
    };

    struct riff_chunk_header
    {
        char identifier[4];
        uint32_t size;
    };
    
    struct wav_fmt_chunk
    {
        uint16_t fmt;
        uint16_t channels;
        uint32_t freq;
        uint32_t bytes_per_sec;
        uint16_t bytes_per_bloc;
        uint16_t bits;
    };

    size = 0;
    std::streampos data_position = 0;
    stream = std::ifstream(path, std::ios::binary);
    riff_master_header master_header;

    stream.read(reinterpret_cast<char*>(&master_header), sizeof(master_header));
    if (stream.eof())
    {
        LOG_WARNING("'", path, "' is too short");
        return;
    }

    if (std::string(master_header.riff_identifier, 4) != "RIFF")
    {
        LOG_WARNING("'", path, "' is not a RIFF file");
        return;
    }

    if (std::string(master_header.format_identifier, 4) != "WAVE")
    {
        LOG_WARNING("'", path, "' is not a valid wav file");
        return;
    }

    while (!stream.eof() || size == 0 || type != sb2d::audio::format::filetype::WAV)
    {
        riff_chunk_header header;
        stream.read(reinterpret_cast<char*>(&header), sizeof(riff_chunk_header));
        
        if (std::string(header.identifier, 4) == "fmt ")
        {
            if (header.size < sizeof(wav_fmt_chunk))
            {
                LOG_WARNING("fmt chunk is too small in '", path, "'");
                return;
            }

            wav_fmt_chunk fmt;
            stream.read(reinterpret_cast<char*>(&fmt), header.size);
           
            type = sb2d::audio::format::filetype::WAV;
            bits = fmt.bits;
            channels = fmt.channels;
            freq = fmt.freq;
        }
        else if (std::string(header.identifier, 4) == "data")
        {
            data_position = stream.tellg();
            size = header.size;
        }
        else
        {
            stream.ignore(header.size);
        }
    }

    if (size == 0)
    {
        type = sb2d::audio::format::filetype::NONE;
        LOG_WARNING("Could not find data chunk in '", path, "'");
        return;
    }

    stream.seekg(data_position);
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
