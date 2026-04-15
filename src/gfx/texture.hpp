#pragma once
#include "gfx.hpp"
#include "core/asset.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include <cstdint>

namespace sb2d::gfx
{
    class texture : public asset<texture>
    {
        private:
            gl_object gl_id;
            glm::ivec2 size;
        public:
            texture(const std::string &path);
            ~texture();

            glm::ivec2 get_size();

            static void set_slot(const texture &t, const int slot);
            static void set_slot(const uint32_t id, const int slot);
            static constexpr int slot_count = 16;
    };
}
