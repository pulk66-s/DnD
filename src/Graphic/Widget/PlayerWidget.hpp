#pragma once

#include "../GraphicNamespace.hpp"
#include "AWidget.hpp"
#include "imgui.h"
#include "SpellWidget.hpp"
#include "WeaponWidget.hpp"
#include "Player/Inventory.hpp"
#include "Player/Money.hpp"
#include "Player/Weapons.hpp"
#include "Player/Spells.hpp"
#include "Player/Skills.hpp"
#include "Player/Stats.hpp"
#include "Player/Actions.hpp"
#include "Player/SavingThrows.hpp"
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
            wplayer::Inventory *invDisplay;
            wplayer::Money *moneyDisplay;
            wplayer::Weapons *weaponsDisplay;
            wplayer::Spells *spellsDisplay;
            wplayer::Skills *skillsDisplay;
            wplayer::Stats *statsDisplay;
            wplayer::SavingThrows *savingThrowsDisplay;
            wplayer::Actions *actionsDisplay;

            void displayEditWindow();
        public:
            PlayerWidget(bool *open = nullptr): PlayerWidget(new player::Player(), open) {};
            PlayerWidget(player::Player *player, bool *open = nullptr)
                : player(player), AWidget(open) {
                    this->invDisplay = new wplayer::Inventory(player->getInv());
                    this->moneyDisplay = new wplayer::Money(player->coins());
                    this->weaponsDisplay = new wplayer::Weapons(player->weapons());
                    this->spellsDisplay = new wplayer::Spells(player->spells());
                    this->skillsDisplay = new wplayer::Skills(player->skills());
                    this->statsDisplay = new wplayer::Stats(player->stats());
                    this->savingThrowsDisplay = new wplayer::SavingThrows(player->saving());
                    this->actionsDisplay = new wplayer::Actions(player);
                };
            void display() override {
                if (this->player == nullptr) {
                    return;
                }
                if (!ImGui::Begin(("Player" + this->player->name()).c_str(), this->open)) {
                    return;
                }
                if (!ImGui::BeginTable("Player infos", 2)) {
                    ImGui::End();
                    return;
                }
                ImGui::TableHeadersRow();
                ImGui::TableNextColumn();
                if (ImGui::Button("Edit")) {
                    this->edit = !this->edit;
                    this->levelInput = this->player->level();
                    strcpy(this->nameBuffer, this->player->name().c_str());
                    strcpy(this->descBuffer, this->player->desc().c_str());
                }
                ImGui::Text("Name: %s", this->player->name().c_str());
                ImGui::Text("Description:");
                ImGui::TextWrapped("%s", this->player->desc().c_str());
                ImGui::Text("Class: %s", this->player->pclass()->name().c_str());
                ImGui::Text("Alignment: %s", this->player->alignment().c_str());
                ImGui::Text("Level: %d", this->player->level());
                ImGui::Text("Proficiency: %d", this->player->proficiency());
                ImGui::Text("HP: %d", this->player->hp());
                ImGui::SameLine();
                ImGui::Text("Max HP: %d", this->player->maxHp());
                ImGui::TableNextColumn();
                this->actionsDisplay->display();
                ImGui::EndTable();
                ImGui::NewLine();
                if (!ImGui::BeginTable("All Stats", 2, ImGuiTableFlags_Resizable)) {
                    ImGui::End();
                    return;
                }
                ImGui::Separator();
                ImGui::TableNextColumn();
                this->statsDisplay->display();
                ImGui::TableNextColumn();
                this->savingThrowsDisplay->display();
                ImGui::EndTable();
                ImGui::Separator();
                if (this->player->armor() != nullptr) {
                    ImGui::Text("Armor: %s", this->player->armor()->name().c_str());
                } else {
                    ImGui::Text("Armor: None");
                }
                ImGui::SameLine();
                ImGui::Text("CA: %d", this->player->armor()->ca());
                if (!ImGui::BeginTable("Inventory", 2, ImGuiTableFlags_Resizable)) {
                    ImGui::End();
                    return;
                }
                ImGui::TableNextColumn();
                this->invDisplay->display();
                ImGui::TableNextColumn();
                this->moneyDisplay->display();
                ImGui::EndTable();
                ImGui::Separator();
                if (!ImGui::BeginTable("To Name", 2, ImGuiTableFlags_Resizable)) {
                    ImGui::End();
                    return;
                }
                ImGui::TableNextColumn();
                this->weaponsDisplay->display();
                ImGui::TableNextColumn();
                this->spellsDisplay->display();
                ImGui::EndTable();
                ImGui::Separator();
                this->skillsDisplay->display();
                if (this->edit) {
                    this->displayEditWindow();
                }
                ImGui::End();
            }
    };
} // namespace dnd::graphic::widget
