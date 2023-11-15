#pragma once

#include "../GraphicNamespace.hpp"
#include "AWidget.hpp"
#include "imgui.h"
#include "../../Player.hpp"
#include <vector>

namespace dnd::graphic::widget
{
    class ClassWidget : public AWidget {
        private:
            std::vector<player::pclass::AClass *> _classes = {
                new player::pclass::Paladin(),
                new player::pclass::Fighter(),
            };
            player::pclass::AClass *selectedClass = nullptr;
            ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                        | ImGuiTableFlags_Borders
                                        | ImGuiTableFlags_RowBg;

        public:
            ClassWidget() {};
            void display() override {
                ImGui::Begin("Player classes");
                ImGui::Text("This is the list of all the classes available in the game.");
                for (player::pclass::AClass *c : this->_classes) {
                    if (ImGui::Button(c->name().c_str())) {
                        this->selectedClass = c;
                    }
                    ImGui::SameLine();
                }
                if (this->selectedClass != nullptr) {
                    ImGui::NewLine();
                    ImGui::Separator();
                    this->displayCharacterSheet(this->selectedClass);
                }
                ImGui::End();
            }

            void displayCharacterSheet(player::pclass::AClass *c) {
                std::vector<player::pclass::ClassTableLine> table = c->table();

                ImGui::Text("Name: %s", c->name().c_str());
                ImGui::Text("Description:");
                ImGui::TextWrapped("%s", c->desc().c_str());
                if (!ImGui::BeginTable("##classTable", 4, this->tableFlags)) {
                    return;
                }
                // Make the columns resizable
                ImGui::TableSetupColumn("Level");
                ImGui::TableSetupColumn("Proficiency bonus");
                ImGui::TableSetupColumn("Features");
                ImGui::TableSetupColumn("Spell slots");
                ImGui::TableHeadersRow();
                for (player::pclass::ClassTableLine line : table) {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::Text("%d", line.level);
                    ImGui::TableNextColumn();
                    ImGui::Text("%d", line.proficiencyBonus);
                    ImGui::TableNextColumn();
                    std::string features = "";
                    for (std::string feature : line.features) {
                        features += feature + "\n";
                    }
                    ImGui::Text("%s", features.c_str());
                    ImGui::TableNextColumn();
                    std::string spellSlots = "";
                    for (int slot : line.spellSlots) {
                        spellSlots += std::to_string(slot) + " ";
                    }
                    ImGui::Text("%s", spellSlots.c_str());
                }
                ImGui::EndTable();
            }
    };
} // namespace dnd::graphic::widget
