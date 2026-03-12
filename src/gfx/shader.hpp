#pragma once
#include "core/asset.hpp"

namespace sb2d::gfx
{
    class shader : public asset<shader>
    {
    private:
        uint32_t program_id;
        void unload_self() override;

    public:
        shader(const std::string& path);
        static void set_current(const std::string& path);
    };
}
