#pragma once

#include "../../GraphicNamespace.hpp"
#include "../AWidget.hpp"
#include "../../../Player.hpp"
#include "imgui.h"
#include "../ItemWidget.hpp"
#include "../../../Objects.hpp"
#include <algorithm>

namespace dnd::graphic::widget::wplayer
{
    class Inventory : public AWidget {
    private:
        objects::items::ItemFactory factory;
        player::Inventory *inventory;
        ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable 
                                    | ImGuiTableFlags_Borders
                                    | ImGuiTableFlags_RowBg;
        bool *editOpen = new bool(false);
        bool *searchOpen = new bool(false);
        std::vector<std::pair<ItemWidget *, bool *>> itemWidgets = {};
        char search[128] = "";
        std::unordered_map<objects::items::AItem *, int *> itemUpdate = {};

        void displaySearch() {
            if (!ImGui::Begin("Search Item", this->searchOpen)) {
                return;
            }
            ImGui::Text("Search Item");
            ImGui::InputText("Name", this->search, IM_ARRAYSIZE(this->search));
            std::vector<std::string> list = factory.list();
            ImGui::Text("Name");
            std::string lowerCaseSearch = std::string(this->search);
            std::transform(lowerCaseSearch.begin(), lowerCaseSearch.end(), lowerCaseSearch.begin(), [](unsigned char c){ return std::tolower(c); });
            for (std::string name : list) {
                std::string lowerCaseName = std::string(this->search);
                std::transform(lowerCaseName.begin(), lowerCaseName.end(), lowerCaseName.begin(), [](unsigned char c){ return std::tolower(c); });
                if (std::string(lowerCaseSearch).empty() || lowerCaseName.find(std::string(lowerCaseSearch)) != std::string::npos) {
                    if (ImGui::Selectable(name.c_str())) {
                        auto it = std::find_if(this->itemUpdate.begin(), this->itemUpdate.end(), [name](std::pair<objects::items::AItem *, int *> i) {
                            return i.first->name() == name;
                        });
                        if (it != this->itemUpdate.end()) {
                            for (std::pair<objects::items::AItem *, int *> p : this->itemUpdate) {
                                if (p.first->name() == name) {
                                    this->itemUpdate[p.first]++;
                                }
                            }
                        } else {
                            this->itemUpdate[this->factory.create(name)] = new int(1);
                        }
                        *this->searchOpen = false;
                    }
                }
            }
            ImGui::End();
        }
        void displayEdit() {
            if (!ImGui::Begin("Edit Inventory", this->editOpen)) {
                return;
            }
            if (ImGui::Button("Update")) {
                *this->editOpen = false;
                for (std::pair<objects::items::AItem *, int *> elem : this->itemUpdate) {
                    this->inventory->setElement(elem.first, *elem.second);
                }
                this->itemUpdate = {};
                this->inventory->clean();
            }
            ImGui::SameLine();
            if (ImGui::Button("Add")) {
                *this->searchOpen = true;
            }
            for (std::pair<objects::items::AItem *, int *> elem : this->itemUpdate) {
                ImGui::InputInt(elem.first->name().c_str(), elem.second);
                ImGui::NewLine();
            }
            ImGui::End();
            if (*this->searchOpen) {
                this->displaySearch();
            }
        }
    public:
        Inventory(player::Inventory *inventory)
            : inventory(inventory) {};
        void display() override {
            if (this->inventory == nullptr) {
                return;
            }
            ImGui::Text("Inventory");
            ImGui::SameLine();
            if (ImGui::Button("Update")) {
                this->itemUpdate = {};
                for (std::pair<objects::items::AItem *, int *> p : this->inventory->inv()) {
                    this->itemUpdate[p.first] = new int(*p.second);
                }
                *this->editOpen = true;
            }
            if (!ImGui::BeginTable("Inventory", 2, this->tableFlags)) {
                return;
            }
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Qte");
            ImGui::TableHeadersRow();
            for (std::pair<objects::items::AItem *, int *> elem : this->inventory->inv()) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                if (ImGui::Selectable(elem.first->name().c_str())) {
                    auto it = std::find_if(this->itemWidgets.begin(), this->itemWidgets.end(), [elem](std::pair<ItemWidget *, bool *> elem2) {
                        return elem2.first->item() == elem.first;
                    });
                    if (it == this->itemWidgets.end()) {
                        bool *open = new bool(true);
                        this->itemWidgets.push_back(std::make_pair(new ItemWidget(elem.first, open), open));
                    } else {
                        *it->second = !*it->second;
                    }
                }
                ImGui::TableNextColumn();
                ImGui::Text("%d", *elem.second);
            }
            ImGui::EndTable();
            if (*this->editOpen) {
                this->displayEdit();
            }
            for (std::pair<ItemWidget *, bool *> elem : this->itemWidgets) {
                if (*elem.second) {
                    elem.first->display();
                }
            }
            this->itemWidgets.erase(
                std::remove_if(
                    this->itemWidgets.begin(),
                    this->itemWidgets.end(),
                    [](std::pair<ItemWidget *, bool *> elem) {
                        return elem.first == nullptr || elem.second == nullptr || !*elem.second;
                    }
                ),
                this->itemWidgets.end()
            );
        }
    };
} // namespace dnd::graphic::widget::wplayer
