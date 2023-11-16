#pragma once

#include "../../GraphicNamespace.hpp"
#include "../AWidget.hpp"
#include "../../../Player.hpp"
#include "imgui.h"

namespace dnd::graphic::widget::wplayer
{
    class Money : public AWidget {
    private:
        std::unordered_map<player::PlayerMoney, int> money = {};
        std::unordered_map<player::PlayerMoney, int> editMoney = {};
        ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                    | ImGuiTableFlags_Borders
                                    | ImGuiTableFlags_RowBg;
        bool *editOpen = new bool(false);

        void resetEditMoney() {
            for (std::pair<player::PlayerMoney, int> c : this->money) {
                this->editMoney[c.first] = 0;
            }
        }
        void displayEdit() {
            if (!ImGui::Begin("Edit Money", this->editOpen)) {
                return;
            }
            for (std::pair<player::PlayerMoney, int> c : this->money) {
                ImGui::InputInt(player::toString(c.first).c_str(), &this->editMoney[c.first]);
                ImGui::NewLine();
            }
            if (ImGui::Button("Update")) {
                for (std::pair<player::PlayerMoney, int> c : this->editMoney) {
                    this->money[c.first] += c.second;
                }
                *this->editOpen = false;
                this->resetEditMoney();
            }
            ImGui::End();
        }
    public:
        Money(std::unordered_map<player::PlayerMoney, int> money)
            : money(money) {};
        void display() override {
            ImGui::Text("Money");
            ImGui::SameLine();
            if (ImGui::Button("Update")) {
                *this->editOpen = true;
            }
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
            if (*this->editOpen) {
                this->displayEdit();
            }
        }
    };
} // namespace dnd::graphic::widget::wplayer
