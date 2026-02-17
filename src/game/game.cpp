#include "game.hpp"
#include "core/log.hpp"
#include "core/sdl_interface.hpp"
#include "core/time.hpp"
#include "debug/debug_ui.hpp"
#include "gfx/gfx.hpp"

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
#if defined (IS_DEBUG)
    LOG_MESSAGE("Build mode: Debug");
#else
    LOG_MESSAGE("Build mode: Release");
#endif

    sb2d::sdl_interface::init();
    sb2d::time::init();
    sb2d::gfx::init();
    sb2d::debug_ui::init();
}

static void s_update()
{
    sb2d::time::update();
    sb2d::sdl_interface::handle_events();

    sb2d::debug_ui::update();

    sb2d::gfx::draw();
}

static void s_terminate()
{
    sb2d::debug_ui::terminate();
    sb2d::sdl_interface::terminate();
    sb2d::gfx::terminate();
}

static bool s_is_running()
{
    return !sb2d::sdl_interface::ready_to_quit();
}
