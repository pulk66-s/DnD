#pragma once

#include "../../GraphicNamespace.hpp"
#include "../AWidget.hpp"
#include "../../../Player.hpp"
#include "imgui.h"
#include <unordered_map>

namespace dnd::graphic::widget::wplayer
{
    class SavingThrows : public AWidget {
    private:
        std::unordered_map<player::PlayerStats, std::pair<int, int>> saving;
        ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                    | ImGuiTableFlags_Borders
                                    | ImGuiTableFlags_RowBg;
    public:
        SavingThrows(std::unordered_map<player::PlayerStats, std::pair<int, int>> saving): saving(saving) {};
        void display() override {
            ImGui::Text("Saving Throws");
            if (!ImGui::BeginTable("Saving Throws", 3, this->tableFlags)) {
                return;
            }
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Bonus");
            ImGui::TableSetupColumn("Proficiency");
            ImGui::TableHeadersRow();
            for (std::pair<player::PlayerStats, std::pair<int, int>> i : this->saving) {
                std::pair<int, int> p = i.second;

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%s", player::toString(i.first).c_str());
                ImGui::TableNextColumn();
                ImGui::Text("%d", p.first);
                ImGui::TableNextColumn();
                ImGui::Text("%d", p.second);
            }
            ImGui::EndTable();
        }
    };
} // namespace dnd::graphic::widget::wplayer
