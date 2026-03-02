#pragma once
#include "asset.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"

namespace sb2d::assets
{
    class texture : public asset<texture>
    {
        private:
            uint32_t gl_id;
            glm::ivec2 size;
        public:
            texture(const std::string &path);
            ~texture();

            glm::ivec2 get_size();

            static void set_slot(const texture &t, const int slot);
    };
}
