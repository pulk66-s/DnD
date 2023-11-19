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
        player::data::DiceStats diceStats;
        ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                    | ImGuiTableFlags_Borders
                                    | ImGuiTableFlags_RowBg;
    public:
        SavingThrows(player::data::DiceStats diceStats): diceStats(diceStats) {};
        void display() override {
            ImGui::Text("Saving Throws");
            if (!ImGui::BeginTable("Saving Throws", 2, this->tableFlags)) {
                return;
            }
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Proficiency");
            ImGui::TableHeadersRow();
            for (std::pair<player::data::DiceStats::PlayerStats, bool> i : this->diceStats.getSaving()) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%s", player::data::DiceStats::toString(i.first).c_str());
                ImGui::TableNextColumn();
                ImGui::Text("%d", i.second);
            }
            ImGui::EndTable();
        }
    };
} // namespace dnd::graphic::widget::wplayer
