#include "gfx.hpp"
#include "SDL3/SDL_video.h"
#include "core/log.hpp"
#include "game/components/sprite.hpp"
#include "glad/glad.h"
#include "imgui/backends/imgui_impl_sdl3.h"
#include "debug/debug_ui.hpp"

using namespace sb2d;

constexpr std::string WINDOW_TITLE = "Sonic Box2D";
constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 480;
constexpr SDL_WindowFlags WINDOW_FLAGS = 
{
    SDL_WINDOW_OPENGL
    | SDL_WINDOW_RESIZABLE
};

static SDL_Window* s_sdl_window;
static SDL_GLContext s_sdl_context;

void gfx::init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    s_sdl_window = SDL_CreateWindow(WINDOW_TITLE.c_str(), WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS);
    s_sdl_context = SDL_GL_CreateContext(s_sdl_window);
    SDL_GL_MakeCurrent(s_sdl_window, s_sdl_context);

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    SDL_GL_SetSwapInterval(0);

    game::components::sprite::init();

    LOG_MESSAGE("Initialized graphics");
}

void gfx::draw()
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    game::components::sprite::draw();
    debug_ui::draw();

    SDL_GL_SwapWindow(s_sdl_window);
}

void gfx::terminate()
{
    game::components::sprite::terminate();

    SDL_DestroyWindow(s_sdl_window);

    LOG_MESSAGE("Terminated graphics");
}

void gfx::init_imgui()
{
#if defined(IS_DEBUG)
    ImGui_ImplSDL3_InitForOpenGL(s_sdl_window, s_sdl_context);
#endif
}
