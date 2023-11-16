#include "MainMenu.hpp"
#include "imgui.h"
#include "../Widget/ClassWidget.hpp"
#include "../Widget/PlayerWidget.hpp"
#include "../Widget/CreatePlayer.hpp"
#include "../Widget/LoadPlayer.hpp"

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
                bool *open = new bool(true);
                this->addWidget(new widget::CreatePlayerWidget(open), open);
            }
            if (ImGui::MenuItem("Load")) {
                bool *open = new bool(true);
                this->addWidget(new widget::LoadPlayerWidget(open), open);
            }
            if (ImGui::MenuItem("Class")) {
                bool *open = new bool(true);
                this->addWidget(new widget::ClassWidget(open), open);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
        for (std::pair<widget::AWidget *, bool *> widget : menus::MainMenuOptionalWidgets) {
            if (widget.first != nullptr && widget.second != nullptr && *widget.second) {
                widget.first->display();
            }
        }
    }
}
