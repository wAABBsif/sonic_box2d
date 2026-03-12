#pragma once
#include <cstdint>
#include <string>

namespace sb2d::game
{
    class component_base
    {
    public:
        enum component_type : uint8_t
        {
            COMPONENT_TRANSFORM,
            COMPONENT_SPRITE,
            COMPONENT_COUNT
        };

        virtual constexpr std::string get_name() = 0;
        virtual void update_debug_inspector() = 0;
    };

    template <typename derived>
    class component : public component_base
    {

    };
}
