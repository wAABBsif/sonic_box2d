#include "time.hpp"
#include <chrono>

using namespace sb2d;

static std::chrono::time_point<std::chrono::steady_clock> s_start_time;
static std::chrono::time_point<std::chrono::steady_clock> s_previous_time;
static std::chrono::time_point<std::chrono::steady_clock> s_current_time;

void time::init()
{
    s_start_time = std::chrono::steady_clock::now();
    s_previous_time = s_start_time;
    s_current_time = s_start_time;
}

void time::update()
{
    s_previous_time = s_current_time;
    s_current_time = std::chrono::steady_clock::now();
}

float time::get_elapsed()
{
    return ((std::chrono::duration<float>)(s_current_time - s_start_time)).count();
}

float time::get_delta()
{
    return ((std::chrono::duration<float>)(s_current_time - s_previous_time)).count();
}
