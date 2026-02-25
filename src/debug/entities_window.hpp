#pragma once

#include "game/entity.hpp"
namespace sb2d::debug_ui::entities_window
{
    void update();
    std::weak_ptr<sb2d::game::entity> get_selection();
}
