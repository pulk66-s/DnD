#include "MainMenu.hpp"
#include "imgui.h"
#include "../Widget/ClassWidget.hpp"
#include "../Widget/PlayerWidget.hpp"
#include "../Widget/CreatePlayer.hpp"

namespace dnd::graphic::menus {
    MainMenu::MainMenu() : AMenu("Main Menu") {
    }

    void MainMenu::display() {
        AMenu::display();
        if (!ImGui::BeginMainMenuBar()) {
            return;
        }
        if (ImGui::BeginMenu("Player")) {
            if (ImGui::MenuItem("Create")) {
                this->addWidget(new widget::CreatePlayerWidget());
            }
            if (ImGui::MenuItem("Class")) {
                this->addWidget(new widget::ClassWidget());
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
