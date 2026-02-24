#pragma once
#include <string>

namespace sb2d::game
{
    class component
    {
    public:
        virtual constexpr std::string get_name() = 0;
    };
}
