#pragma once
#include <cstdint>

namespace sb2d::audio
{
    struct format
    {
    public:
        uint8_t bits;
        uint8_t channels;   
        uint32_t freq;
        uint32_t size;
        char* buffer;
    
    protected:
        format() = default;
        ~format();

    public:
        bool isValid();
    };
}
