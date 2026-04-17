#include "gfx.hpp"
#include "SDL3/SDL_video.h"
#include "core/color.hpp"
#include "core/log.hpp"
#include "game/components/sprite.hpp"
#include "gfx/framebuffer.hpp"
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
static color s_color;

void gfx::init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    s_sdl_window = SDL_CreateWindow(WINDOW_TITLE.c_str(), WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS);
    s_sdl_context = SDL_GL_CreateContext(s_sdl_window);
    SDL_GL_MakeCurrent(s_sdl_window, s_sdl_context);

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SDL_GL_SetSwapInterval(0);

    game::components::sprite::init();

    framebuffer::reset_current_framebuffer();

    LOG_MESSAGE("Initialized graphics");
}

void gfx::init_imgui()
{
#if defined(IS_DEBUG)
    ImGui_ImplSDL3_InitForOpenGL(s_sdl_window, s_sdl_context);
#endif
}

void gfx::terminate()
{
    game::components::sprite::terminate();

    SDL_DestroyWindow(s_sdl_window);

    LOG_MESSAGE("Terminated graphics");
}

glm::ivec2 gfx::get_window_size()
{
    glm::ivec2 result;
    SDL_GetWindowSize(s_sdl_window, &result.x, &result.y);
    return result;
}

void gfx::render_to_framebuffer(const framebuffer& fb, const color clear_color, const glm::mat3 world_to_screen)
{
    framebuffer::set_current_framebuffer(fb);
    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT);
    game::components::sprite::draw();
    framebuffer::reset_current_framebuffer();
}

void gfx::render_to_screen()
{
    framebuffer::reset_current_framebuffer();
    debug_ui::draw();

    SDL_GL_SwapWindow(s_sdl_window);
}
