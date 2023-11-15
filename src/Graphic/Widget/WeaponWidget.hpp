#pragma once

#include "../GraphicNamespace.hpp"
#include "AWidget.hpp"
#include "imgui.h"
#include "../../Player.hpp"
#include <iostream>

namespace dnd::graphic::widget
{
    class WeaponWidget : public AWidget {
    private:
        objects::items::Weapon *weapon = nullptr;
        bool *open = nullptr;
    public:
        WeaponWidget(bool *open, objects::items::Weapon *weapon = new objects::items::Weapon())
            : weapon(weapon), open(open) {};
        void display() {
            ImGui::Begin(("Weapon " + this->weapon->name()).c_str(), this->open);
            ImGui::Text("Name: %s", this->weapon->name().c_str());
            ImGui::Text("Description: %s", this->weapon->desc().c_str());
            ImGui::Text("Damages: %s", this->weapon->damages()->toString().c_str());
            ImGui::End();
        }
        objects::items::Weapon *getWeapon() const { return this->weapon; };
        void setWeapon(objects::items::Weapon *weapon) { this->weapon = weapon; };
    };
} // namespace dnd::graphic::widget
