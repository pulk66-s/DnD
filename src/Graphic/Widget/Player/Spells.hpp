#pragma once

#include "../../GraphicNamespace.hpp"
#include "../AWidget.hpp"
#include "../../../Player.hpp"
#include "imgui.h"
#include "../SpellWidget.hpp"
#include <vector>

namespace dnd::graphic::widget::wplayer
{
    class Spells : public AWidget {
    private:
        std::vector<std::pair<SpellWidget *, bool *>> spellWidgets = {};
        player::data::Skills skills;
        ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                    | ImGuiTableFlags_Borders
                                    | ImGuiTableFlags_RowBg;
    public:
        Spells(player::data::Skills skills): skills(skills) {};
        void display() override {
            ImGui::Text("Spells");
            if (!ImGui::BeginTable("Spells", 2, this->tableFlags)) {
                return;
            }
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Level");
            ImGui::TableHeadersRow();
            for (player::spells::ASpell *s : this->skills.spells()) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                if (ImGui::Selectable(s->name().c_str())) {
                    auto it = std::find_if(this->spellWidgets.begin(), this->spellWidgets.end(), [s](std::pair<SpellWidget *, bool *> p) {
                        return p.first->getSpell() == s;
                    });
                    if (it == this->spellWidgets.end()) {
                        bool *open = new bool(true);
                        this->spellWidgets.push_back(std::make_pair(new SpellWidget(open, s), open));
                    } else {
                        *(it->second) = !*(it->second);
                    }
                }
                ImGui::TableNextColumn();
                ImGui::Text("%d", s->level());
            }
            ImGui::EndTable();
            for (std::pair<SpellWidget *, bool *> i : this->spellWidgets) {
                if (*(i.second)) {
                    i.first->display();
                }
            }
        }
    };
} // namespace dnd::graphic::widget::wplayer
