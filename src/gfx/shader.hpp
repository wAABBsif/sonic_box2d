#pragma once
#include "core/asset.hpp"
#include "glm/glm.hpp"
#include "gfx.hpp"

namespace sb2d::gfx
{
    class shader : public asset<shader>
    {
    private:
        gl_object program_id;

    public:
        shader(const std::string& path);
        ~shader();
        static void set_current(const shader& shader);

        void set_int(const std::string &name, const int32_t value);
        void set_uint(const std::string &name, const uint32_t value);
        void set_float(const std::string &name, const float value);
        void set_vec2(const std::string &name, const glm::vec2 value);
        void set_ivec2(const std::string &name, const glm::ivec2 value);
        void set_mat3(const std::string &name, const glm::mat3 value);
    };
}
