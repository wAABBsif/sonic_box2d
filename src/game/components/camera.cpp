#include "camera.hpp"
#include "gfx/framebuffer.hpp"

using namespace sb2d::game::components;
using namespace sb2d::gfx;

camera::camera(const glm::ivec2 texture_size, const color clear_color)
    : clear_color(clear_color), framebuffer(gfx::framebuffer(texture_size))
{}

framebuffer camera::get_framebuffer()
{
    return framebuffer;
}
