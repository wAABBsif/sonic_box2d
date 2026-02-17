#pragma once
#include "SDL3/SDL_events.h"

namespace sb2d::debug_ui
{
    void init();
    void terminate();

    void update();
    void draw();
    void handle_events(const SDL_Event *event);
}
