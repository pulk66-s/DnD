#pragma once

#include "../../GraphicNamespace.hpp"
#include "../AWidget.hpp"
#include <vector>
#include "../../../Player.hpp"
#include "imgui.h"

namespace dnd::graphic::widget::wplayer
{
    class Weapons : public AWidget {
    private:
        std::vector<objects::items::Weapon *> weapons;
        std::vector<std::pair<WeaponWidget *, bool *>> weaponWidgets = {};
        ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                    | ImGuiTableFlags_Borders
                                    | ImGuiTableFlags_RowBg;
    public:
        Weapons(std::vector<objects::items::Weapon *> weapons): weapons(weapons) {};
        void display() override {
            ImGui::Text("Weapons");
            if (!ImGui::BeginTable("Weapons", 2, this->tableFlags)) {
                return;
            }
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Damages");
            ImGui::TableHeadersRow();
            for (objects::items::Weapon *w : this->weapons) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                if (ImGui::Selectable(w->name().c_str())) {
                    auto it = std::find_if(this->weaponWidgets.begin(), this->weaponWidgets.end(), [w](std::pair<WeaponWidget *, bool *> p) {
                        return p.first->getWeapon() == w;
                    });
                    if (it == this->weaponWidgets.end()) {
                        bool *open = new bool(true);
                        this->weaponWidgets.push_back(std::make_pair(new WeaponWidget(open, w), open));
                    } else {
                        *(it->second) = !*(it->second);
                    }
                }
                ImGui::TableNextColumn();
                ImGui::Text("%s", w->damages()->toString().c_str());
            }
            for (std::pair<WeaponWidget *, bool *> i : this->weaponWidgets) {
                if (*(i.second)) {
                    i.first->display();
                }
            }
            ImGui::EndTable();
        }
    };
} // namespace dnd::graphic::widget::wplayer
