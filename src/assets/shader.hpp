#pragma once
#include "asset.hpp"

namespace sb2d::assets
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
