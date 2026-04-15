#pragma once
#include <cstdint>
#include "glm/glm.hpp"

namespace sb2d::gfx
{
    class framebuffer
    {
    private:
        glm::ivec2 size;
        uint32_t fbo;
        uint32_t texture_id;

        void create_fbo();
        void create_texture();

    public:
        framebuffer(const glm::ivec2 size);

        glm::ivec2 get_size();
        void resize(const glm::ivec2 size);
    
        static void set_current_framebuffer(const framebuffer& buffer);
        static void reset_current_framebuffer();
        
        static void set_texture_slot(const framebuffer& buffer, const int slot);
    };
}
