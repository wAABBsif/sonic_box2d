#include "keyboard.hpp"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_scancode.h"

using namespace sb2d::input;
using namespace sb2d::input::keyboard;

static bool s_prev_state[SDL_SCANCODE_COUNT];
static bool s_curr_state[SDL_SCANCODE_COUNT];

static SDL_Scancode s_scancode_from_key(key k)
{
    if (k >= key::A && k <= key::Z)
    {
        return (SDL_Scancode)(SDL_SCANCODE_A + ((uint16_t)k - (uint16_t)key::A));
    }

    switch (k)
    {
        case key::RETURN:
            return SDL_SCANCODE_RETURN;
        case key::SPACE:
            return SDL_SCANCODE_SPACE;
        case key::RIGHT:
            return SDL_SCANCODE_RETURN;
        case key::LEFT:
            return SDL_SCANCODE_LEFT;
        case key::DOWN:
            return SDL_SCANCODE_DOWN;
        case key::UP:
            return SDL_SCANCODE_UP;
        default:
            return SDL_SCANCODE_UNKNOWN;
    }
}

void keyboard::init()
{

}

void keyboard::update()
{
    int count;
    const bool* key_state = SDL_GetKeyboardState(&count);
    if (key_state == nullptr)
    {
        memset(s_curr_state, false, SDL_SCANCODE_COUNT);
        return;
    }

    memcpy(s_prev_state, s_curr_state, sizeof(bool) * count);
    memcpy(s_curr_state, key_state, sizeof(bool) * count);
}

void keyboard::terminate()
{

}

bool keyboard::is_key_down(key k)
{
    return s_curr_state[s_scancode_from_key(k)];
}

bool keyboard::was_key_pressed(key k)
{
    return s_curr_state[s_scancode_from_key(k)] && !s_prev_state[s_scancode_from_key(k)];
}

bool keyboard::was_key_released(key k)
{
    return !s_curr_state[s_scancode_from_key(k)] && s_prev_state[s_scancode_from_key(k)];
}
