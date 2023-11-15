#pragma once

#include "../../GraphicNamespace.hpp"
#include "../AWidget.hpp"
#include "../../../Player.hpp"
#include "imgui.h"
#include <vector>

namespace dnd::graphic::widget::wplayer
{
    class Skills : public AWidget {
    private:
        std::vector<player::skills::ASkill *> skills;
        ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                    | ImGuiTableFlags_Borders
                                    | ImGuiTableFlags_RowBg;
    public:
        Skills(std::vector<player::skills::ASkill *> skills): skills(skills) {};
        void display() override {
            ImGui::Text("Skills");
            if (!ImGui::BeginTable("Skills", 2, this->tableFlags)) {
                return;
            }
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Description");
            ImGui::TableHeadersRow();
            for (player::skills::ASkill *s : this->skills) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%s", s->name().c_str());
                ImGui::TableNextColumn();
                ImGui::Text("%s", s->desc().c_str());
            }
            ImGui::EndTable();
        }
    };
} // namespace dnd::graphic::widget::wplayer
