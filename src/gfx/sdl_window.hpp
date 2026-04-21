#pragma once
#include "SDL3/SDL_video.h"
#include "glm/fwd.hpp"
#include "window.hpp"
#include <string>

namespace sb2d::gfx
{
    class sdl_window : public window
    {
    private:
        SDL_Window* window;
        SDL_GLContext context;
    public:
        sdl_window(const std::string& title, const glm::ivec2 size);
        ~sdl_window();
    
        void swap_buffers() override;

        glm::ivec2 get_size() override;
    
        void init_imgui() override;
    };
}
