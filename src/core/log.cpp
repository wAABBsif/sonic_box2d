#include "log.hpp"

void sb2d::log_set_color(log_color color)
{
#if defined(WIN32)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (color == LOG_COLOR_WHITE)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    else if (color == LOG_COLOR_YELLOW)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    else if (color == LOG_COLOR_RED)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
#elif defined(linux)
    if (color == log_color::WHITE)
        std::cout << "\x1b[0m";
    else if (color == log_color::YELLOW)
        std::cout << "\x1b[33m";
    else if (color == log_color::RED)
        std::cout << "\x1b[31m";
#endif
}

void sb2d::log_flush()
{
    std::cout << std::endl;
}
