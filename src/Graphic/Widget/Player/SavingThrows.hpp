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
        std::unordered_map<player::PlayerStats, bool> saving;
        ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                    | ImGuiTableFlags_Borders
                                    | ImGuiTableFlags_RowBg;
    public:
        SavingThrows(std::unordered_map<player::PlayerStats, bool> saving): saving(saving) {};
        void display() override {
            ImGui::Text("Saving Throws");
            if (!ImGui::BeginTable("Saving Throws", 2, this->tableFlags)) {
                return;
            }
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Proficiency");
            ImGui::TableHeadersRow();
            for (std::pair<player::PlayerStats, bool> i : this->saving) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%s", player::toString(i.first).c_str());
                ImGui::TableNextColumn();
                ImGui::Text("%d", i.second);
            }
            ImGui::EndTable();
        }
    };
} // namespace dnd::graphic::widget::wplayer
