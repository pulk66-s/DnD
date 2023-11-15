#pragma once

#include "../../GraphicNamespace.hpp"
#include "../AWidget.hpp"
#include "../SkillWidget.hpp"
#include "../../../Player.hpp"
#include "imgui.h"
#include <vector>

namespace dnd::graphic::widget::wplayer
{
    class Skills : public AWidget {
    private:
        std::vector<player::skills::ASkill *> skills;
        std::vector<std::pair<SkillWidget *, bool *>> skillWidgets = {};
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
                if (ImGui::Selectable(s->name().c_str())) {
                    auto it = std::find_if(this->skillWidgets.begin(), this->skillWidgets.end(),
                        [s](std::pair<SkillWidget *, bool *> p) {
                            return p.first->getSkill() == s;
                        }
                    );

                    if (it == this->skillWidgets.end()) {
                        bool *open = new bool(true);
                        this->skillWidgets.push_back(std::make_pair(new SkillWidget(s, open), open));
                    } else {
                        *(it->second) = !*(it->second);
                    }
                }
                ImGui::TableNextColumn();
                ImGui::Text("%s", s->desc().c_str());
            }
            for (std::pair<SkillWidget *, bool *> p : this->skillWidgets) {
                if (*p.second) {
                    p.first->display();
                }
            }
            ImGui::EndTable();
        }
    };
} // namespace dnd::graphic::widget::wplayer
