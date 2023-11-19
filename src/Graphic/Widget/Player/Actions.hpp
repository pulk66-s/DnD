#pragma once

#include "../../GraphicNamespace.hpp"
#include "../AWidget.hpp"
#include "../../../Player.hpp"
#include "imgui.h"
#include <optional>
#include <algorithm>

namespace dnd::graphic::widget::wplayer
{
    class Actions : public AWidget {
    private:
        player::Player *player;
        objects::items::Weapon *weapon = nullptr;
        bool *attackOpen = new bool(false);
        bool *attackConfirmation = new bool(false);
        bool *takeDamageOpen = new bool(false);
        bool *spendMoneyOpen = new bool(false);
        bool *spendMoneyConfirmation = new bool(false);
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
            if (*this->attackOpen) {
                this->displayAttack();
            }
            if (*this->takeDamageOpen) {
                this->displayTakeDamages();
            }
            if (*this->spendMoneyOpen) {
                this->displaySpendMoney();
            }
        }
    };
} // namespace dnd::graphic::widget::wplayer
