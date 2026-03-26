#include "texture.hpp"
#include "core/log.hpp"
#include "glm/fwd.hpp"
#include <GLES2/gl2.h>
#include <cstddef>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace sb2d::gfx;

texture::texture(const std::string &path)
{
    this->gl_id = 0;
    stbi_uc *img = stbi_load(path.c_str(), &this->size.x, &this->size.y, NULL, 4);
    if (img == NULL)
    {
        LOG_WARNING("Texture '", path, "' could not be loaded");
        return;
    }

    if (this->size.x == 0 || this->size.y == 0)
    {
        LOG_WARNING("Texture '", path, "' has invalid size");
        return;
    }

    glGenBuffers(1, &this->gl_id);
    glBindTexture(GL_TEXTURE_2D, this->gl_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->size.x, this->size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(reinterpret_cast<void *>(img));

    LOG_MESSAGE("Texture '", path, "' loaded");
}

texture::~texture()
{
    glDeleteTextures(1, &this->gl_id);
}

glm::ivec2 texture::get_size()
{
    return this->size;
}

void texture::set_slot(const texture &t, const int slot)
{
    if (slot >= slot_count)
        LOG_WARNING("Texture slot ", slot, " may not be supported!");
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, t.gl_id);
}
