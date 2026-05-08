#pragma once
#include <string>
#include <cstdint>
#include "fstream"
namespace sb2d::audio
{
    struct format
    {
    public:
        enum class filetype : uint8_t
        {
            NONE,
            WAV
        };

    private:
        filetype type;
        
    public:
        uint8_t bits;
        uint8_t channels;   
        uint32_t freq;
        uint32_t size;

    private:
        std::ifstream stream;

        format() = delete;
        void load_wav(const std::string& path);

    public:
        format(const std::string& path);
        ~format() = default;

        void read(char* buffer, uint32_t size);
        bool isValid();
    };
}
