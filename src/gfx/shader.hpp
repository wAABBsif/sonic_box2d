#pragma once
#include "core/asset.hpp"

namespace sb2d::gfx
{
    class shader : public asset<shader>
    {
    private:
        uint32_t program_id;
    public:
        shader(const std::string &path);
        ~shader();

        static void set_current(const shader& s);
        static void reset_current();
    };
}
