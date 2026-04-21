#include "gfx.hpp"
#include "window.hpp"
#include "framebuffer.hpp"
#include "texture.hpp"
#include "glad/glad.h"
#include "game/game.hpp"

using namespace sb2d::gfx;

void framebuffer::create_fbo()
{
    if (glIsFramebuffer(fbo))
        glDeleteFramebuffers(1, &fbo);

    glGenFramebuffers(1, &fbo);
}

void framebuffer::create_texture()
{
    if (glIsTexture(texture_id))
        glDeleteTextures(1, &texture_id);

    glGenTextures(1, &texture_id);

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (glIsFramebuffer(fbo))
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}

framebuffer::framebuffer(const glm::ivec2 size)
    : size(size)
{
    create_fbo();
    create_texture();
}

framebuffer::~framebuffer()
{
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &texture_id);
}

glm::ivec2 framebuffer::get_size()
{
    return size;
}

void framebuffer::resize(const glm::ivec2 size)
{
    this->size = size;
    create_texture();
}

void framebuffer::set_current_framebuffer(const framebuffer& buffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, buffer.fbo);
    glViewport(0, 0, buffer.size.x, buffer.size.y);
}

void framebuffer::reset_current_framebuffer()
{
    gfx::window& window = game::get_main_window();
    glm::ivec2 size = window.get_size();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, size.x, size.y);
}

void framebuffer::set_texture_slot(const framebuffer& buffer, const int slot)
{
    texture::set_slot(buffer.texture_id, slot);
}
