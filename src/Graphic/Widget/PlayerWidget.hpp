#pragma once

#include "../GraphicNamespace.hpp"
#include "AWidget.hpp"
#include "imgui.h"
#include "SpellWidget.hpp"
#include "WeaponWidget.hpp"
#include "../../Player.hpp"
#include <vector>

namespace dnd::graphic::widget
{
    class PlayerWidget : public AWidget {
        private:
            player::Player *player;
            bool edit = false;
            char nameBuffer[128] = {0};
            char descBuffer[2048] = {0};
            int levelInput = 0;
            ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                        | ImGuiTableFlags_Borders
                                        | ImGuiTableFlags_RowBg;
            std::vector<std::pair<SpellWidget *, bool *>> spellWidgets = {};
            std::vector<std::pair<WeaponWidget *, bool *>> weaponWidgets = {};

            void displayEditWindow();
            void displayBasicInfos();
            void displayInventory();
            void displayPlayerStats();
            void displaySavingThrows();
            void displaySkills();
        public:
            PlayerWidget(): player(new player::Player()) {};
            PlayerWidget(player::Player *player): player(player) {};
            void display() override {
                ImGui::Begin("Player");
                this->displayBasicInfos();
                if (this->edit) {
                    this->displayEditWindow();
                }
                for (std::pair<SpellWidget *, bool *> i : this->spellWidgets) {
                    if (*(i.second)) {
                        i.first->display();
                    }
                }
                for (std::pair<WeaponWidget *, bool *> i : this->weaponWidgets) {
                    if (*(i.second)) {
                        i.first->display();
                    }
                }
                ImGui::End();
            }
    };
} // namespace dnd::graphic::widget
