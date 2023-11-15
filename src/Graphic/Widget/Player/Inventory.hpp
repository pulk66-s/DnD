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
        bool insert;
        ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                    | ImGuiTableFlags_Borders
                                    | ImGuiTableFlags_RowBg;
    public:
        Inventory(player::Inventory *inventory, bool insert = true)
            : inventory(inventory), insert(insert) {};
        void display() override {
            if (this->inventory == nullptr) {
                return;
            }
            if (!this->insert) {
                ImGui::Begin("Inventory");
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
            if (!this->insert) {
                ImGui::End();
            }
        }
    };
} // namespace dnd::graphic::widget::wplayer