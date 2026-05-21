#pragma once
#include <cstdint>

namespace sb2d::input::keyboard
{
    enum class key : uint16_t
    {
        INVALID,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        X,
        Y,
        Z,
        RETURN,
        SPACE,
        RIGHT,
        LEFT,
        DOWN,
        UP
    };

    void init();
    void terminate();
    void update();

    bool is_key_down(key k);
    bool was_key_pressed(key k);
    bool was_key_released(key k);
}
