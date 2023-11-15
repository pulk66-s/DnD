#pragma once

#include "../GraphicNamespace.hpp"
#include "AWidget.hpp"
#include "../../Player.hpp"
#include "imgui.h"

namespace dnd::graphic::widget
{
    class SkillWidget : public AWidget {
    private:
        player::skills::ASkill *skill;
        bool *open;
    public:
        SkillWidget(player::skills::ASkill *skill, bool *open): skill(skill), open(open) {};
        void display() override {
            ImGui::Begin(("Skill " + this->skill->name()).c_str(), this->open);
            ImGui::Text("Name: %s", this->skill->name().c_str());
            ImGui::Text("Description:");
            ImGui::TextWrapped("%s", this->skill->desc().c_str());
            ImGui::End();
        }
        player::skills::ASkill *getSkill() { return this->skill; };
    };
} // namespace dnd::graphic::widget
