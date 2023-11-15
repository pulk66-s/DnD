#pragma once

#include "../../GraphicNamespace.hpp"
#include "../AWidget.hpp"
#include "../../../Player.hpp"
#include "imgui.h"

namespace dnd::graphic::widget::wplayer
{
    class Inventory : public AWidget {
    private:
        player::Inventory *inventory;
        ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                    | ImGuiTableFlags_Borders
                                    | ImGuiTableFlags_RowBg;
    public:
        Inventory(player::Inventory *inventory)
            : inventory(inventory) {};
        void display() override {
            if (this->inventory == nullptr) {
                return;
            }
            ImGui::Text("Inventory");
            if (!ImGui::BeginTable("Inventory", 2, this->tableFlags)) {
                return;
            }
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Qte");
            ImGui::TableHeadersRow();
            for (std::pair<std::string, int> elem : this->inventory->inv()) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%s", elem.first.c_str());
                ImGui::TableNextColumn();
                ImGui::Text("%d", elem.second);
            }
            ImGui::EndTable();
        }
    };
} // namespace dnd::graphic::widget::wplayer
