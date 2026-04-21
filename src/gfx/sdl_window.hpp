#pragma once
#include "SDL3/SDL_video.h"
#include "window.hpp"

namespace sb2d::gfx
{
    class sdl_window : public window
    {
    private:
        SDL_Window* window;
        SDL_GLContext context;
    public:
        sdl_window();
        ~sdl_window();
    
        void swap_buffers() override;

        glm::ivec2 get_size() override;
    
        void init_imgui() override;
    };
}
