#pragma once 

#include "../../GraphicNamespace.hpp"
#include "../AWidget.hpp"
#include "../../../Player.hpp"
#include "imgui.h"
#include <unordered_map>

namespace dnd::graphic::widget::wplayer
{
    class Stats : public AWidget {
    private:
        std::unordered_map<player::PlayerStats, std::pair<int, int>> stats;
        ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                    | ImGuiTableFlags_Borders
                                    | ImGuiTableFlags_RowBg;
    public:
        Stats(std::unordered_map<player::PlayerStats, std::pair<int, int>> stats): stats(stats) {};
        void display() override {
            ImGui::Text("Stats");
            if (!ImGui::BeginTable("Stats", 3, this->tableFlags)) {
                return;
            }
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Value");
            ImGui::TableSetupColumn("Bonus");
            ImGui::TableHeadersRow();
            for (std::pair<player::PlayerStats, std::pair<int, int>> i : this->stats) {
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
