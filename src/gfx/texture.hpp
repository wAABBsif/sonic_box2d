#pragma once
#include "core/asset.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"

namespace sb2d::gfx
{
    class texture : public asset<texture>
    {
        private:
            uint32_t gl_id;
            glm::ivec2 size;
        public:
            texture(const std::string &path);
            void unload_self() override;

            static texture* load(const std::string& path);
            static bool unload(const std::string& path);
            static texture* get(const std::string& path);

            glm::ivec2 get_size();

            static void set_slot(const texture &t, const int slot);
            static constexpr int slot_count = 16;
    };
}
