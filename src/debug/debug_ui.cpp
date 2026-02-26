#include "debug_ui.hpp"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl3.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "gfx/gfx.hpp"

#include "stats_window.hpp"
#include "entities_window.hpp"
#include "components_window.hpp"

using namespace sb2d;

#if defined (IS_DEBUG)
constexpr ImGuiConfigFlags CONFIG_FLAGS = 
{
    ImGuiConfigFlags_NavEnableKeyboard
    | ImGuiConfigFlags_DockingEnable
};
#endif

static bool s_is_enabled;

void debug_ui::init()
{
#if defined (IS_DEBUG)
    ImGui::CreateContext();
    auto& io = ImGui::GetIO();
    io.ConfigFlags |= CONFIG_FLAGS;

    ImGui::StyleColorsDark();

    gfx::init_imgui();
    ImGui_ImplOpenGL3_Init();
#endif
}

void debug_ui::terminate()
{
#if defined (IS_DEBUG)
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
#endif
}

void debug_ui::update()
{
#if defined (IS_DEBUG)
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(0, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

    if (!s_is_enabled)
        return;

    //this is temporary obviously
    stats_window::update();
    entities_window::update();
    components_window::update();
#endif
}

void debug_ui::draw()
{
#if defined (IS_DEBUG)
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
}

void debug_ui::handle_events(const SDL_Event *event)
{
#if defined (IS_DEBUG)
    ImGui_ImplSDL3_ProcessEvent(event);

	if (event->type == SDL_EVENT_KEY_DOWN)
		if (event->key.key == SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1))
			s_is_enabled = !s_is_enabled;
#endif
}
