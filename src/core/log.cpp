#include "log.hpp"
#if defined(WIN32)
#include <windows.h>
#endif

void sb2d::log_set_color(log_color color)
{
#if defined(WIN32)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (color == log_color::WHITE)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    else if (color == log_color::YELLOW)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    else if (color == log_color::RED)
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
