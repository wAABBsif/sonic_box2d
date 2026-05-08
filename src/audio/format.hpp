#pragma once
#include <string>
#include <cstdint>

namespace sb2d::audio
{
    struct format
    {
    public:
        enum class filetype : uint8_t
        {
            WAV
        };

        filetype type;
        uint8_t bits;
        uint8_t channels;   
        uint32_t freq;
        uint32_t size;
        char* buffer;
    
    protected:
        format() = delete;
        ~format();

    public:
        format(const std::string& path);
        bool isValid();
    };
}
