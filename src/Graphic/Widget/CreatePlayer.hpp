#pragma once

#include "../GraphicNamespace.hpp"
#include "AWidget.hpp"
#include "imgui.h"
#include "../../Lib/Json.hpp"
#include "../../Player.hpp"

namespace dnd::graphic::widget
{
    class CreatePlayerWidget : public AWidget {
    private:
        bool error = false;
        bool success = false, playerExists = false;
        std::vector<std::string> errors = {};
        char nameBuffer[128] = {0};
        char descBuffer[2048] = {0};
        std::string choseRace = "Unknown";
        std::string chosenClass = "Unknown";
        std::unordered_map<player::PlayerStats, std::pair<int, int>> stats = {
            {player::STR, {0, 0}},
            {player::DEX, {0, 0}},
            {player::CON, {0, 0}},
            {player::INT, {0, 0}},
            {player::WIS, {0, 0}},
            {player::CHA, {0, 0}}
        };
        std::unordered_map<player::PlayerStats, bool> saving = {
            {player::STR, false},
            {player::DEX, false},
            {player::CON, false},
            {player::INT, false},
            {player::WIS, false},
            {player::CHA, false}
        };
        std::string alignment = "Unknown";
        player::Player *player = nullptr;

        void raceForm() {
            if (ImGui::BeginMenu(("Race: " + this->choseRace).c_str())) {
                if (ImGui::MenuItem("Elf")) {
                    this->choseRace = "Elf";
                }
                if (ImGui::MenuItem("Dwarf")) {
                    this->choseRace = "Dwarf";
                }
                ImGui::EndMenu();
            }
        }
        void classForm() {
            if (ImGui::BeginMenu(("Class: " + this->chosenClass).c_str())) {
                if (ImGui::MenuItem("Paladin")) {
                    this->chosenClass = "Paladin";
                }
                if (ImGui::MenuItem("Fighter")) {
                    this->chosenClass = "Fighter";
                }
                ImGui::EndMenu();
            }
        }
        void statsForm() {
            if (ImGui::BeginMenu("Stats")) {
                for (auto &stat : this->stats) {
                    if (ImGui::BeginMenu(player::toString(stat.first).c_str())) {
                        ImGui::InputInt("Value", &stat.second.first);
                        ImGui::InputInt("Modifier", &stat.second.second);
                        ImGui::EndMenu();
                    }
                }
                ImGui::EndMenu();
            }
        }
        void savingThrowsForm() {
            if (ImGui::BeginMenu("Saving throws")) {
                for (auto &save : this->saving) {
                    ImGui::Checkbox(player::toString(save.first).c_str(), &save.second);
                }
                ImGui::EndMenu();
            }
        }
        void alignmentForm() {
            std::vector<std::vector<std::string>> aligments = {
                {"LG", "NG", "CG"},
                {"LN", "N", "CN"},
                {"LE", "NE", "CE"}
            };

            if (ImGui::BeginMenu(("Alignment: " + this->alignment).c_str())) {
                if (ImGui::BeginTable("ALignment Table", 3)) {
                    ImGui::TableNextColumn();
                    for (std::vector<std::string> &row : aligments) {
                        ImGui::TableNextRow();
                        for (std::string &align : row) {
                            ImGui::TableNextColumn();
                            if (ImGui::MenuItem(align.c_str())) {
                                this->alignment = align;
                            }
                        }
                    }
                    ImGui::EndTable();
                }
                ImGui::EndMenu();
            }
        }
        bool checkPlayer() {
            this->errors.clear();
            if (this->choseRace == "Unknown") {
                this->errors.push_back("You didn't choose a race");
            }
            if (this->chosenClass == "Unknown") {
                this->errors.push_back("You didn't choose a class");
            }
            if (this->alignment == "Unknown") {
                this->errors.push_back("You didn't choose an alignment");
            }
            return this->errors.empty();
        }
        void savingButton() {
            if (ImGui::Button("Save")) {
                this->success = true;
                if (!this->checkPlayer()) {
                    this->error = true;
                    return;
                }
                this->player = new player::Player(
                    this->nameBuffer,
                    this->descBuffer,
                    new player::pclass::Paladin(),
                    1
                );

                player->alignment(this->alignment);
                player->stats(this->stats);
                player->saving(this->saving);
                this->playerExists = player->exists();
            }
        }
        void errorMessage() {
            ImGui::Begin("Error", &this->error, ImGuiWindowFlags_AlwaysAutoResize);
            for (auto &error : this->errors) {
                ImGui::Text(error.c_str());
            }
            ImGui::End();
        }
    public:
        CreatePlayerWidget() : AWidget() {}
        CreatePlayerWidget(bool *open) : AWidget(open) {}
        void display() override {
            if (this->error) {
                this->errorMessage();
            }
            ImGui::Begin("Create player", this->open);
            ImGui::InputText("Name", this->nameBuffer, IM_ARRAYSIZE(this->nameBuffer));
            ImGui::InputTextMultiline("Description", this->descBuffer, IM_ARRAYSIZE(this->descBuffer));
            this->raceForm();
            this->classForm();
            this->statsForm();
            this->savingThrowsForm();
            this->alignmentForm();
            this->savingButton();
            if (this->success) {
                if (this->playerExists) {
                    ImGui::Begin("Success", &this->success, ImGuiWindowFlags_AlwaysAutoResize);
                    ImGui::Text("A player with this name already exists");
                    if (ImGui::Button("Overwrite")) {
                        this->player->saveJson();
                        delete this->player;
                        this->player = nullptr;
                        this->playerExists = false;
                    }
                    ImGui::End();
                } else {
                    if (this->player != nullptr) {
                        this->player->saveJson();
                        delete this->player;
                        this->player = nullptr;
                    }
                    ImGui::Begin("Success", &this->success, ImGuiWindowFlags_AlwaysAutoResize);
                    ImGui::Text("Player saved");
                    ImGui::End();
                }
            }
            ImGui::End();
        }
    };
} // namespace dnd::graphic::widget
