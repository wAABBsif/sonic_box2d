#include "sdl_window.hpp"
#include "SDL3/SDL_video.h"
#include "imgui/backends/imgui_impl_sdl3.h"
#include "glad/glad.h"
#include <string>
#include "core/log.hpp"

using namespace sb2d::gfx;

constexpr std::string WINDOW_TITLE = "Sonic Box2D";
constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 480;
constexpr SDL_WindowFlags WINDOW_FLAGS = 
{
    SDL_WINDOW_OPENGL
    | SDL_WINDOW_RESIZABLE
};

sdl_window::sdl_window()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS);
    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SDL_GL_SetSwapInterval(0);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    LOG_MESSAGE("Initialized SDL Window");
}

sdl_window::~sdl_window()
{
    SDL_DestroyWindow(window);
    LOG_MESSAGE("Terminated SDL window");
}

void sdl_window::swap_buffers()
{
    SDL_GL_SwapWindow(window);
}

glm::ivec2 sdl_window::get_size()
{
    glm::ivec2 result;
    SDL_GetWindowSize(window, &result.x, &result.y);
    return result;
}

void sdl_window::init_imgui()
{
#if defined(IS_DEBUG)
    ImGui_ImplSDL3_InitForOpenGL(window, context);    
#endif
}
