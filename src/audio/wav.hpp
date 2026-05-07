#pragma once
#include "format.hpp"
#include <string>

namespace sb2d::audio
{
    struct wav : public format
    {
        static wav load(const std::string& path);
    };
}
