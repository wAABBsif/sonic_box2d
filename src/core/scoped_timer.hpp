#pragma once
#include <chrono>
#include <string>

namespace sb2d
{
    class scoped_timer
    {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        std::string name;
    public:
        scoped_timer(std::string name = "Timer");
        ~scoped_timer();
    };
}
