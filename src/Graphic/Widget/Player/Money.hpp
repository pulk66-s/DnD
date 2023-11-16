#pragma once

#include "../../GraphicNamespace.hpp"
#include "../AWidget.hpp"
#include "../../../Player.hpp"
#include "imgui.h"

namespace dnd::graphic::widget::wplayer
{
    class Money : public AWidget {
    private:
        std::unordered_map<player::PlayerMoney, int> &money;
        std::unordered_map<player::PlayerMoney, int> editMoney = {};
        ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                    | ImGuiTableFlags_Borders
                                    | ImGuiTableFlags_RowBg;

    public:
        Money(std::unordered_map<player::PlayerMoney, int> &money)
            : money(money) {};
        void display() override {
            ImGui::Text("Money");
            if (!ImGui::BeginTable("Money", 2, this->tableFlags)) {
                return;
            }
            ImGui::TableSetupColumn("Type");
            ImGui::TableSetupColumn("Qte");
            ImGui::TableHeadersRow();
            for (std::pair<player::PlayerMoney, int> c : this->money) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%s", player::toString(c.first).c_str());
                ImGui::TableNextColumn();
                ImGui::Text("%d", c.second);
            }
            ImGui::EndTable();
        }
    };
} // namespace dnd::graphic::widget::wplayer
