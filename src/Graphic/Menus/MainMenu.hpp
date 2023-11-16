#pragma once

#include "../GraphicNamespace.hpp"
#include "AMenu.hpp"
#include <string>
#include <vector>

namespace dnd::graphic::menus
{
    static std::vector<std::pair<widget::AWidget *, bool *>> MainMenuOptionalWidgets = {};
    class MainMenu : public AMenu {
    public:
        MainMenu();
        void display() override;
    };
} // namespace dnd::graphic::menus
