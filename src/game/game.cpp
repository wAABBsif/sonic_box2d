#include "game.hpp"
#include "core/log.hpp"
#include "core/sdl_interface.hpp"
#include "core/time.hpp"
#include "debug/debug_ui.hpp"
#include "game/entity.hpp"
#include "game/system.hpp"
#include "gfx/gfx.hpp"
#include <gfx/renderer.hpp>

using namespace sb2d;

static void s_init();
static void s_update();
static void s_terminate();
static bool s_is_running();

void game::run()
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

    sdl_interface::init();
    time::init();
    gfx::init();
    debug_ui::init();
    game::entity::init();
    game::system_base::init();
}

static void s_update()
{
    time::update();
    sdl_interface::handle_events();

    game::system_base::update();
    game::entity::update();
    debug_ui::update();

    gfx::draw();
}

static void s_terminate()
{
    game::entity::terminate();
    debug_ui::terminate();
    sdl_interface::terminate();
    gfx::terminate();
}

static bool s_is_running()
{
    return !sdl_interface::ready_to_quit();
}
