#include "game.hpp"
#include "core/log.hpp"
#include "core/sdl_interface.hpp"
#include "core/time.hpp"
#include "debug/debug_ui.hpp"
#include "game/component.hpp"
#include "game/entity.hpp"
#include "game/system.hpp"
#include "gfx/window.hpp"
#include "gfx/sdl_window.hpp"
#include "gfx/renderer.hpp"
#include "audio/device.hpp"
#include "input/keyboard.hpp"

using namespace sb2d;

static void s_init();
static void s_update();
static void s_terminate();
static bool s_is_running();

static gfx::window* s_window;
static audio::device* s_audio_device;

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
    s_window = new gfx::sdl_window("Sonic Box2D", glm::ivec2(640, 480));
    s_audio_device = new audio::device();
    debug_ui::init();
    sb2d::input::keyboard::init();
    game::entity::init();
    game::system_base::init();
}

static void s_update()
{
    time::update();
    sdl_interface::handle_events();
    sb2d::input::keyboard::update();

    game::system_base::update();
    debug_ui::update();

    s_window->render_to_screen();
}

static void s_terminate()
{
    game::system_base::terminate();
    game::entity::terminate();
    sb2d::input::keyboard::terminate();
    debug_ui::terminate();
    delete s_window;
    delete s_audio_device;
    sdl_interface::terminate();    
}

static bool s_is_running()
{
    return !sdl_interface::ready_to_quit();
}

gfx::window& game::get_main_window()
{
    return *s_window;
}
