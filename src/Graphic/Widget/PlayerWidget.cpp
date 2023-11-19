#include "PlayerWidget.hpp"

namespace dnd::graphic::widget
{
    void PlayerWidget::displayEditWindow() {
        ImGui::Begin("Edit Player");
        ImGui::InputText("Name", this->nameBuffer, IM_ARRAYSIZE(this->nameBuffer));
        ImGui::InputTextMultiline("Description", this->descBuffer, IM_ARRAYSIZE(this->descBuffer));
        ImGui::InputInt("Level", &this->levelInput);
        if (ImGui::Button("Save")) {
            this->player->name(this->nameBuffer);
            this->player->desc(this->descBuffer);
            this->player->stats().level(this->levelInput);
            this->edit = false;
        }
        ImGui::End();
    }
} // namespace dnd::graphic::widget
