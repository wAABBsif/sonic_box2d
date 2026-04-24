#include "window.hpp"
#include "core/color.hpp"
#include "core/log.hpp"
#include "game/components/sprite.hpp"
#include "game/systems/sprite_renderer.hpp"
#include "gfx/framebuffer.hpp"
#include "glad/glad.h"
#include "debug/debug_ui.hpp"
#include "glm/ext/matrix_transform.hpp"

using namespace sb2d;
using namespace sb2d::gfx;

static SDL_Window* s_sdl_window;
static SDL_GLContext s_sdl_context;
static color s_color;

void window::render_to_framebuffer(const framebuffer& fb, const color clear_color, const glm::mat3 world_to_screen)
{
    framebuffer::set_current_framebuffer(fb);
    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT);
    game::systems::sprite_renderer::draw(world_to_screen);
    framebuffer::reset_current_framebuffer();
}

void window::render_to_screen()
{
    framebuffer::reset_current_framebuffer();
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    game::systems::sprite_renderer::draw(glm::identity<glm::mat3>());
    debug_ui::draw();

    swap_buffers();
}
