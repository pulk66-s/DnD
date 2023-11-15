#include "MainMenu.hpp"
#include "imgui.h"
#include "../Widget/ClassWidget.hpp"
#include "../Widget/PlayerWidget.hpp"

namespace dnd::graphic::menus {
    MainMenu::MainMenu() : AMenu("Main Menu") {
        this->addWidget(new widget::ClassWidget());
        this->addWidget(new widget::PlayerWidget());
    }
}
