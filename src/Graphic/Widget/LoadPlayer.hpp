#pragma once

#include "../GraphicNamespace.hpp"
#include "AWidget.hpp"
#include "imgui.h"
#include "../../Lib/Json.hpp"

namespace dnd::graphic::widget
{
    class LoadPlayerWidget : public AWidget {
    private:
        std::vector<std::string> players = lib::json::Json::listsFiles("files/players");
        std::string selected = "";
        bool *openConfirm = new bool(true);
    public:
        LoadPlayerWidget() {}
        LoadPlayerWidget(bool *open) : AWidget(open) {}
        void display() {
            ImGui::Begin("Load Player", this->open);
            ImGui::Text("Select the player you want to load");
            int i = 0;
            for (std::string name : this->players) {
                if (ImGui::Button(name.c_str())) {
                    this->selected = name;
                }
                if (i++ % 3 != 2)
                    ImGui::SameLine();
                else
                    ImGui::NewLine();
            }
            if (this->selected != "") {
                ImGui::Begin("Player Load Confirmation", this->openConfirm);
                ImGui::Text("Are you sure you want to load %s?", this->selected.c_str());
                if (ImGui::Button("Yes")) {
                    lib::json::Json json("files/players/" + this->selected);
                    json.load();
                    player::Player *player = new player::Player(json.get());
                    bool *open = new bool(true);
                    menus::MainMenuOptionalWidgets.push_back(std::make_pair(new widget::PlayerWidget(player, open), open));
                    *this->open = false;
                    *this->openConfirm = false;
                    this->selected = "";
                }
                ImGui::End();
            }
            ImGui::End();
        }
    };
} // namespace dnd::graphic::widget
