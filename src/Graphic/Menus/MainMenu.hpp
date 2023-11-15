#pragma once

#include "../GraphicNamespace.hpp"
#include "AMenu.hpp"
#include <string>

namespace dnd::graphic::menus
{
    class MainMenu : public AMenu {
    public:
        MainMenu();
        void display() override;
    };
} // namespace dnd::graphic::menus
