#include "stats_window.hpp"
#include "core/time.hpp"
#include "imgui.h"

using namespace sb2d;
using namespace sb2d::debug_ui;

#if defined (IS_DEBUG)
constexpr float TIME_BETWEEN_REFRESHES = 0.1f;
static float s_refresh_timer;

static float s_frametime;
#endif

static void s_refresh_stats();

void stats_window::update()
{
#if defined (IS_DEBUG)
    s_refresh_timer -= time::get_delta();
    if (s_refresh_timer < 0)
    {
        s_refresh_stats();
        s_refresh_timer = TIME_BETWEEN_REFRESHES;
    }

    ImGui::Begin("Statistics");
    ImGui::Text("Frame Time: %.3fms", s_frametime * 1000);
    ImGui::Text("Frame Rate: %.0f FPS", 1.0f / s_frametime);
    ImGui::End();
#endif
}

static void s_refresh_stats()
{
#if defined (IS_DEBUG)
    s_frametime = time::get_delta();
#endif
}
