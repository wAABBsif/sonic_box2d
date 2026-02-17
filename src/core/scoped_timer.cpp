#include "scoped_timer.hpp"
#include "log.hpp"
#include <chrono>

sb2d::scoped_timer::scoped_timer(std::string name)
{
    this->name = name;
    this->start = std::chrono::high_resolution_clock::now();
}

sb2d::scoped_timer::~scoped_timer()
{
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> elapsed = end - start;
    LOG_MESSAGE(name, " took ", elapsed.count() * 1000, "ms");
}
