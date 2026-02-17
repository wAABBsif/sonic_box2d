#include "sdl_interface.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "core/log.hpp"
#include "debug/debug_ui.hpp"

constexpr SDL_InitFlags INIT_FLAGS = 
{
    SDL_INIT_EVENTS
    | SDL_INIT_VIDEO
    | SDL_INIT_JOYSTICK
    | SDL_INIT_GAMEPAD
};

static bool s_is_ready_to_quit;

void sb2d::sdl_interface::init()
{
    if (!SDL_Init(INIT_FLAGS))
    {
        LOG_ERROR("Could not initialize SDL");
        exit(1);
    }

    s_is_ready_to_quit = false;

    LOG_MESSAGE("Initialized SDL");
}

void sb2d::sdl_interface::terminate()
{
    SDL_Quit();

    LOG_MESSAGE("Terminated SDL");
}

bool sb2d::sdl_interface::ready_to_quit()
{
    return s_is_ready_to_quit;
}

void sb2d::sdl_interface::handle_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
            s_is_ready_to_quit = true;

        sb2d::debug_ui::handle_events(&event);
    }
}
