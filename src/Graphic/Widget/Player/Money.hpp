#pragma once

#include "../../GraphicNamespace.hpp"
#include "../AWidget.hpp"
#include "../../../Player.hpp"
#include "imgui.h"

namespace dnd::graphic::widget::wplayer
{
    class Money : public AWidget {
    private:
        player::data::Money &money;
        player::data::Money editMoney = {};
        ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                    | ImGuiTableFlags_Borders
                                    | ImGuiTableFlags_RowBg;

    public:
        Money(player::data::Money &money)
            : money(money) {};
        void display() override {
            ImGui::Text("Money");
            if (!ImGui::BeginTable("Money", 2, this->tableFlags)) {
                return;
            }
            ImGui::TableSetupColumn("Type");
            ImGui::TableSetupColumn("Qte");
            ImGui::TableHeadersRow();
            for (std::pair<player::data::Money::MoneyType, int> c : this->money.get()) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%s", player::data::Money::toString(c.first).c_str());
                ImGui::TableNextColumn();
                ImGui::Text("%d", c.second);
            }
            ImGui::EndTable();
        }
    };
} // namespace dnd::graphic::widget::wplayer
