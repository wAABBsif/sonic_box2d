#pragma once
#include "gfx/window.hpp"
#include "audio/device.hpp"
#include "phys/world.hpp"

namespace sb2d::game
{
    void run();

    gfx::window& get_main_window();
    audio::device& get_audio_device();
    phys::world& get_world();
}
