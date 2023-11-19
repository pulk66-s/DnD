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
        player::data::Spells spells;
        ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                    | ImGuiTableFlags_Borders
                                    | ImGuiTableFlags_RowBg;
        bool *limitOpen = new bool(false);

        void displaySpellsLimit() {
            if (!ImGui::Begin("Spells Limit", this->limitOpen)) {
                return;
            }
            if (ImGui::BeginTable("Spells Limit", 3, this->tableFlags)) {
                ImGui::TableSetupColumn("Level");
                ImGui::TableSetupColumn("Limit");
                ImGui::TableSetupColumn("Casted");
                ImGui::TableHeadersRow();
                for (int i = 0; i < 10; i++) {
                    int l = this->spells.limit(i);
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::Text("%d", i);
                    ImGui::TableNextColumn();
                    ImGui::Text("%d", l);
                    ImGui::TableNextColumn();
                    ImGui::Text("%d", this->spells.casted(i));
                }
                ImGui::EndTable();
            }
            ImGui::End();
        }                         
    public:
        Spells(player::data::Spells spells): spells(spells) {};
        void display() override {
            ImGui::Text("Spells");
            ImGui::SameLine();
            if (ImGui::Button("Spells Limit")) {
                *(this->limitOpen) = !*(this->limitOpen);
            }
            if (!ImGui::BeginTable("Spells", 2, this->tableFlags)) {
                return;
            }
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Level");
            ImGui::TableHeadersRow();
            for (player::spells::ASpell *s : this->spells.list()) {
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
            if (*this->limitOpen) {
                this->displaySpellsLimit();
            }
        }
    };
} // namespace dnd::graphic::widget::wplayer
