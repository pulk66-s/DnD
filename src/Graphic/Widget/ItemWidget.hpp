#pragma once

#include "../GraphicNamespace.hpp"
#include "AWidget.hpp"
#include "../../Objects.hpp"
#include "imgui.h"

namespace dnd::graphic::widget
{
    class ItemWidget : public AWidget {
    private:
        objects::items::AItem *_item;
    public:
        ItemWidget(objects::items::AItem *item, bool *open = nullptr): _item(item), AWidget(open) {};
        void display() override {
            ImGui::Begin(("Item " + this->_item->name()).c_str(), this->open);
            ImGui::Text("Name: %s", this->_item->name().c_str());
            ImGui::TextWrapped("Description: %s", this->_item->desc().c_str());
            ImGui::End();
        }
        objects::items::AItem *item() const { return this->_item; };
    };
} // namespace dnd::graphic::widget
