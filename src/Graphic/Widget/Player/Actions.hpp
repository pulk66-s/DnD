#pragma once

#include "../../GraphicNamespace.hpp"
#include "../AWidget.hpp"
#include "../../../Player.hpp"
#include "imgui.h"
#include <optional>
#include <algorithm>
#include <optional>

namespace dnd::graphic::widget::wplayer
{
    class Actions : public AWidget {
    private:
        player::Player *player;
        objects::items::Weapon *weapon = nullptr;
        bool *attackOpen = new bool(false);
        bool *attackConfirmation = new bool(false);
        bool *savingThrowsOpen = new bool(false);
        bool *statDiceOpen = new bool(false);
        bool *statDiceOpenConfirmation = new bool(false);
        bool *savingThrowsOpenConfirmation = new bool(false);
        std::optional<int> savingResult = std::nullopt;
        std::optional<int> statResult = std::nullopt;
        bool *takeDamageOpen = new bool(false);
        bool *spendMoneyOpen = new bool(false);
        bool *spendMoneyConfirmation = new bool(false);
        player::data::DiceStats::PlayerStats savingStat = player::data::DiceStats::STR;
        player::data::DiceStats::PlayerStats diceStat = player::data::DiceStats::STR;
        int *takeDamage = new int(0);
        std::optional<int> attackDamages = std::nullopt;
        std::unordered_map<player::data::Money::MoneyType, int *> spendMoney = {
            {player::data::Money::MoneyType::PC, new int(0)},
            {player::data::Money::MoneyType::PA, new int(0)},
            {player::data::Money::MoneyType::PE, new int(0)},
            {player::data::Money::MoneyType::PO, new int(0)},
            {player::data::Money::MoneyType::PP, new int(0)}
        };

        void displayAttack() {
            if (!ImGui::Begin("Attack", this->attackOpen)) {
                return;
            }
            ImGui::Text("Choose a weapon to attack with:");
            if (ImGui::BeginMenu(("Weapon " + (this->weapon == nullptr ? "" : this->weapon->name())).c_str())) {
                for (objects::items::Weapon *weapon : this->player->equipment().weapons()) {
                    if (ImGui::MenuItem(weapon->name().c_str())) {
                        this->weapon = weapon;
                    }
                }
                ImGui::EndMenu();
            }
            if (ImGui::Button("Attack")) {
                if (this->weapon != nullptr) {
                    *this->attackConfirmation = true;
                }
            }
            if (*this->attackConfirmation) {
                if (ImGui::Begin("Attack confirmation", this->attackConfirmation)) {
                    ImGui::Text("Attack confirmation");
                    ImGui::TextWrapped(
                        "Are you sure you want to attack with the weapon: '%s' tha can deal %s damages ?", 
                        this->weapon->name().c_str(), 
                        this->weapon->damages()->toString().c_str()
                    );
                    if (ImGui::Button("Yes")) {
                        if (!this->attackDamages.has_value()) {
                            this->attackDamages = this->weapon->damages()->roll();
                        }
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("No")) {
                        *this->attackConfirmation = false;
                    }
                    if (this->attackDamages.has_value()) {
                        ImGui::Text("You dealt %d damages", this->attackDamages.value());
                    }
                    ImGui::End();
                }
            }
            ImGui::End();
            if (*this->attackConfirmation == false) {
                if (this->attackDamages.has_value()) {
                    this->attackDamages = std::nullopt;
                }
            }
        }
        void displayTakeDamages() {
            ImGui::Begin("Take Damage", this->takeDamageOpen);
            ImGui::Text("How many damages do you want to take ?");
            ImGui::InputInt("Damages", this->takeDamage);
            if (ImGui::Button("Take")) {
                this->player->stats().hp(-*this->takeDamage);
            }
            ImGui::End();
        }
        void displaySpendMoney() {
            if (!ImGui::Begin("Spend Money", this->spendMoneyOpen)) {
                return;
            }
            ImGui::Text("How much money do you want to spend ?");
            for (std::pair<player::data::Money::MoneyType, int *> p : this->spendMoney) {
                ImGui::InputInt(player::data::Money::toString(p.first).c_str(), p.second);
            }
            if (ImGui::Button("Spend")) {
                *this->spendMoneyConfirmation = true;
            }
            if (*this->spendMoneyConfirmation) {
                if (ImGui::Begin("Spend money confirmation", this->spendMoneyConfirmation)) {
                    ImGui::Text("Spend money confirmation");
                    ImGui::TextWrapped("Do you want to spend:");
                    for (std::pair<player::data::Money::MoneyType, int *> p : this->spendMoney) {
                        ImGui::Text("%s: %d", player::data::Money::toString(p.first).c_str(), *p.second);
                    }
                    if (ImGui::Button("Yes")) {
                        std::unordered_map<player::data::Money::MoneyType, int> c = this->player->money().get();
                        for (std::pair<player::data::Money::MoneyType, int *> p : this->spendMoney) {
                            c[p.first] -= *p.second < 0 ? 0 : *p.second;
                            c[p.first] = c[p.first] < 0 ? 0 : c[p.first];
                        }
                        this->player->money().set(c);
                        *this->spendMoneyConfirmation = false;
                        *this->spendMoneyOpen = false;
                    }
                    ImGui::End();
                }
            }
            ImGui::End();
        }
        void displaySavingThrows() {
            if (!ImGui::Begin("Throw saving dice", this->savingThrowsOpen)) {
                return;
            }
            ImGui::Text("Select your saving dice");
            if (ImGui::BeginMenu("Category")) {
                for (int i = 0; i < 6; i++) {
                    if (ImGui::MenuItem(player::data::DiceStats::toString((player::data::DiceStats::PlayerStats)i).c_str())) {
                        this->savingStat = (player::data::DiceStats::PlayerStats)i;
                        *this->savingThrowsOpenConfirmation = true;
                        this->savingResult = std::nullopt;
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::End();
        }
        void displaySavingThrowsConfirmation() {
            if (!ImGui::Begin("Throw saving dice Confirmation", this->savingThrowsOpenConfirmation)) {
                return;
            }
            ImGui::TextWrapped("Are you sure you want to launch a saving throw ?");
            ImGui::Text(("Dice Type: " + player::data::DiceStats::toString(this->savingStat)).c_str());
            bool diceSaving = this->player->diceStats().getSaving(this->savingStat);
            player::Dice dice(1, 20, 0);
            if (diceSaving) {
                dice.bonus(this->player->stats().proficiency());
            }
            ImGui::Text(("Dice: " + dice.toString()).c_str());
            if (ImGui::Button("Yes")) {
                if (!this->savingResult.has_value()) {
                    this->savingResult = std::make_optional(dice.roll());
                }
            }
            if (this->savingResult.has_value()) {
                ImGui::Text("You rolled %d", this->savingResult.value());
            }
            ImGui::End();
        }
        void displayStatDice() {
            if (!ImGui::Begin("Throw stat dice", this->savingThrowsOpen)) {
                return;
            }
            ImGui::Text("Select your stat dice");
            if (ImGui::BeginMenu("Category")) {
                for (int i = 0; i < 6; i++) {
                    if (ImGui::MenuItem(player::data::DiceStats::toString((player::data::DiceStats::PlayerStats)i).c_str())) {
                        this->diceStat = (player::data::DiceStats::PlayerStats)i;
                        *this->statDiceOpenConfirmation = true;
                        this->statResult = std::nullopt;
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::End();
        }
        void displayStatDiceConfirmation() {
            if (!ImGui::Begin("Throw stat dice Confirmation", this->savingThrowsOpenConfirmation)) {
                return;
            }
            ImGui::TextWrapped("Are you sure you want to launch a stat dice ?");
            ImGui::Text(("Dice Type: " + player::data::DiceStats::toString(this->diceStat)).c_str());
            player::Dice dice(1, 20, this->player->diceStats().getBonus(this->diceStat));
            ImGui::Text(("Dice: " + dice.toString()).c_str());
            if (ImGui::Button("Yes")) {
                if (!this->statResult.has_value()) {
                    this->statResult = std::make_optional(dice.roll());
                }
            }
            if (this->statResult.has_value()) {
                ImGui::Text("You rolled %d", this->statResult.value());
            }
            ImGui::End();
        }
    public:
        Actions(player::Player *player): player(player) {};
        void display() override {
            if (ImGui::Button("Attack")) {
                *this->attackOpen = !*this->attackOpen;
            }
            if (ImGui::Button("Take Damage")) {
                *this->takeDamageOpen = !*this->takeDamageOpen;
            }
            if (ImGui::Button("Spend Money")) {
                *this->spendMoneyOpen = !*this->spendMoneyOpen;
            }
            if (ImGui::Button("Saving Throws")) {
                *this->savingThrowsOpen = !*this->savingThrowsOpen;
            }
            if (ImGui::Button("Stat Dice")) {
                *this->statDiceOpen = !*this->statDiceOpen;
            }
            if (*this->attackOpen) {
                this->displayAttack();
            }
            if (*this->takeDamageOpen) {
                this->displayTakeDamages();
            }
            if (*this->spendMoneyOpen) {
                this->displaySpendMoney();
            }
            if (*this->savingThrowsOpen) {
                this->displaySavingThrows();
            }
            if (*this->savingThrowsOpenConfirmation) {
                this->displaySavingThrowsConfirmation();
            }
            if (*this->statDiceOpen) {
                this->displayStatDice();
            }
            if (*statDiceOpenConfirmation) {
                this->displayStatDiceConfirmation();
            }
        }
    };
} // namespace dnd::graphic::widget::wplayer
