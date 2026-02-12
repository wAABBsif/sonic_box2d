#pragma once

namespace sb2d::sdl_interface
{
    void init();
    void terminate();
    
    bool ready_to_quit();
    void handle_events();
}
