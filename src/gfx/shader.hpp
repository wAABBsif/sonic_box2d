#pragma once
#include "core/asset.hpp"
#include "glm/glm.hpp"

namespace sb2d::gfx
{
    class shader : public asset<shader>
    {
    private:
        uint32_t program_id;
        void unload_self() override;

    public:
        shader(const std::string& path);
        static void set_current(const shader& shader);

        static shader* load(const std::string& path);
        static bool unload(const std::string& path);
        static shader* get(const std::string& path);
    };
}
