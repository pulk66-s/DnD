#pragma once

#include "../GraphicNamespace.hpp"
#include "AWidget.hpp"
#include "imgui.h"
#include "../../Player.hpp"
#include <iostream>

namespace dnd::graphic::widget
{
    class SpellWidget : public AWidget {
    private:
        player::spells::ASpell *spell = nullptr;
        bool *open = nullptr;
    public:
        SpellWidget(bool *open, player::spells::ASpell *spell = new player::spells::ASpell())
            : spell(spell), open(open) {};
        void display() {
            ImGui::Begin(("Spell" + this->spell->name()).c_str(), this->open);
            ImGui::Text("Name: %s", this->spell->name().c_str());
            ImGui::Text("Description: %s", this->spell->desc().c_str());
            ImGui::Text("Level: %d", this->spell->level());
            ImGui::End();
        }
        player::spells::ASpell *getSpell() const { return this->spell; };
        void setSpell(player::spells::ASpell *spell) { this->spell = spell; };
    };
} // namespace dnd::graphic::widget
