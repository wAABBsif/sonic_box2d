#pragma once

#include <cstdint>
#include <ostream>
#include <iostream>

#define LOG_MESSAGE(...)                                                \
({                                                                      \
    sb2d::log_raw("[MESSAGE - ", __FILE_NAME__, ":", __LINE__, "]");    \
    sb2d::log_raw(__VA_ARGS__);                                         \
    sb2d::log_flush();                                                  \
})

#define LOG_WARNING(...)                                                \
({                                                                      \
    sb2d::log_set_color(sb2d::log_color::YELLOW);                       \
    sb2d::log_raw("[WARNING - ", __FILE_NAME__, ":", __LINE__, "]");    \
    sb2d::log_raw(__VA_ARGS__);                                         \
    sb2d::log_flush();                                                  \
    sb2d::log_set_color(sb2d::log_color::WHITE);                        \
})

#define LOG_ERROR(...)                                                  \
({                                                                      \
    sb2d::log_set_color(sb2d::log_color::RED);                          \
    sb2d::log_raw("[ERROR - ", __FILE_NAME__, ":", __LINE__, "]");      \
    sb2d::log_raw(__VA_ARGS__);                                         \
    sb2d::log_flush();                                                  \
    sb2d::log_set_color(sb2d::log_color::WHITE);                        \
})

namespace sb2d
{
    enum class log_color : uint8_t
    {
        WHITE,
        YELLOW,
        RED
    };

    void log_set_color(log_color color);
    void log_flush();

    template<typename... Ts>
    void log_raw(const Ts &... args)
    {
        ([&]
        {
            std::cout << args;
        } (), ...);
        std::cout << " ";
    } 
}
