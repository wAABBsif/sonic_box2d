#include "game.hpp"
#include "core/log.hpp"
#include "core/sdl_interface.hpp"

static void s_init();
static void s_update();
static void s_terminate();
static bool s_is_running();

void sb2d::game::run()
{
    s_init();
    LOG_MESSAGE("Game initialized");
    while (s_is_running())
    {
        s_update();
    }

    s_terminate();
    LOG_MESSAGE("Game terminated");
}

static void s_init()
{
    sb2d::sdl_interface::init();
}

static void s_update()
{
    sb2d::sdl_interface::handle_events();
}

static void s_terminate()
{
    sb2d::sdl_interface::terminate();
}

static bool s_is_running()
{
    return sb2d::sdl_interface::ready_to_quit();
}
