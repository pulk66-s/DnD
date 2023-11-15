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
            this->player->level(this->levelInput);
            this->edit = false;
        }
        ImGui::End();
    }

    void PlayerWidget::displayPlayerStats() {
        ImGui::Text("Stats");
        if (!ImGui::BeginTable("Stats", 3, this->tableFlags)) {
            return;
        }
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Value");
        ImGui::TableSetupColumn("Bonus");
        ImGui::TableHeadersRow();
        for (std::pair<player::PlayerStats, std::pair<int, int>> i : this->player->stats()) {
            std::pair<int, int> p = i.second;

            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%s", player::toString(i.first).c_str());
            ImGui::TableNextColumn();
            ImGui::Text("%d", p.first);
            ImGui::TableNextColumn();
            ImGui::Text("%d", p.second);
        }
        ImGui::EndTable();
    }

    void PlayerWidget::displayBasicInfos() {
        if (ImGui::Button("Edit")) {
            this->edit = !this->edit;
            this->levelInput = this->player->level();
            strcpy(this->nameBuffer, this->player->name().c_str());
            strcpy(this->descBuffer, this->player->desc().c_str());
        }
        ImGui::Text("Name: %s", this->player->name().c_str());
        ImGui::Text("Description: %s", this->player->desc().c_str());
        ImGui::Text("Class: %s", this->player->pclass()->name().c_str());
        ImGui::Text("Alignment: %s", this->player->alignment().c_str());
        ImGui::Text("Level: %d", this->player->level());
        ImGui::Text("Proficiency: %d", this->player->proficiency());
        ImGui::Text("HP: %d", this->player->hp());
        ImGui::SameLine();
        ImGui::Text("Max HP: %d", this->player->maxHp());
        ImGui::NewLine();
        if (!ImGui::BeginTable("All Stats", 2, ImGuiTableFlags_Resizable)) {
            return;
        }
        ImGui::Separator();
        ImGui::TableNextColumn();
        this->displayPlayerStats();
        ImGui::TableNextColumn();
        this->displaySavingThrows();
        ImGui::EndTable();
        this->displayInventory();
        this->displaySkills();
    }

    void PlayerWidget::displaySavingThrows() {
        ImGui::Text("Saving Throws");
        if (!ImGui::BeginTable("Saving Throws", 3, this->tableFlags)) {
            return;
        }
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Bonus");
        ImGui::TableSetupColumn("Proficiency");
        ImGui::TableHeadersRow();
        for (std::pair<player::PlayerStats, std::pair<int, int>> i : this->player->saving()) {
            std::pair<int, int> p = i.second;

            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%s", player::toString(i.first).c_str());
            ImGui::TableNextColumn();
            ImGui::Text("%d", p.first);
            ImGui::TableNextColumn();
            ImGui::Text("%d", p.second);
        }
        ImGui::EndTable();
    }

    void PlayerWidget::displayInventory() {
        ImGui::Separator();
        ImGui::Text("Armor: %s", this->player->armor()->name().c_str());
        ImGui::SameLine();
        ImGui::Text("CA: %d", this->player->armor()->ca());
        if (!ImGui::BeginTable("Inventory", 2)) {
            return;
        }
        ImGui::TableNextColumn();
        ImGui::Text("Inventory");
        if (!ImGui::BeginTable("Inventory", 2, this->tableFlags)) {
            return;
        }
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Qte");
        ImGui::TableHeadersRow();
        for (std::pair<std::string, int> elem : this->player->getInv().inv()) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%s", elem.first.c_str());
            ImGui::TableNextColumn();
            ImGui::Text("%d", elem.second);
        }
        ImGui::EndTable();
        ImGui::TableNextColumn();
        ImGui::Text("Money");
        if (!ImGui::BeginTable("Money", 2, this->tableFlags)) {
            return;
        }
        ImGui::TableSetupColumn("Type");
        ImGui::TableSetupColumn("Qte");
        ImGui::TableHeadersRow();
        for (std::pair<player::PlayerMoney, int> c : this->player->coins()) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%s", player::toString(c.first).c_str());
            ImGui::TableNextColumn();
            ImGui::Text("%d", c.second);
        }
        ImGui::EndTable();
        ImGui::EndTable();
    }

    void PlayerWidget::displaySkills() {
        ImGui::Separator();
        if (!ImGui::BeginTable("Money", 2, ImGuiTableFlags_Resizable)) {
            return;
        }
        ImGui::TableNextColumn();
        ImGui::Text("Weapons");
        if (!ImGui::BeginTable("Weapons", 2, this->tableFlags)) {
            return;
        }
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Damages");
        ImGui::TableHeadersRow();
        for (objects::items::Weapon *w : this->player->weapons()) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            if (ImGui::Selectable(w->name().c_str())) {
                auto it = std::find_if(this->weaponWidgets.begin(), this->weaponWidgets.end(), [w](std::pair<WeaponWidget *, bool *> p) {
                    return p.first->getWeapon() == w;
                });
                if (it == this->weaponWidgets.end()) {
                    bool *open = new bool(true);
                    this->weaponWidgets.push_back(std::make_pair(new WeaponWidget(open, w), open));
                } else {
                    *(it->second) = !*(it->second);
                }
            }
            ImGui::TableNextColumn();
            ImGui::Text("%s", w->damages()->toString().c_str());
        }
        ImGui::EndTable();
        ImGui::TableNextColumn();
        ImGui::Text("Spells");
        if (!ImGui::BeginTable("Spells", 2, this->tableFlags)) {
            return;
        }
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Level");
        ImGui::TableHeadersRow();
        for (player::spells::ASpell *s : this->player->spells()) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            if (ImGui::Selectable(s->name().c_str())) {
                auto it = std::find_if(this->spellWidgets.begin(), this->spellWidgets.end(), [s](std::pair<SpellWidget *, bool *> p) {
                    return p.first->getSpell() == s;
                });
                if (it == this->spellWidgets.end()) {
                    bool *open = new bool(true);
                    this->spellWidgets.push_back(std::make_pair(new SpellWidget(open, s), open));
                } else {
                    *(it->second) = !*(it->second);
                }
            }
            ImGui::TableNextColumn();
            ImGui::Text("%d", s->level());
        }
        ImGui::EndTable();
        ImGui::EndTable();
        ImGui::Separator();
        ImGui::Text("Skills");
        if (!ImGui::BeginTable("Skills", 2, this->tableFlags | ImGuiTableFlags_ScrollX)) {
            return;
        }
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Description");
        ImGui::TableHeadersRow();
        for (player::skills::ASkill *s : this->player->skills()) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%s", s->name().c_str());
            ImGui::TableNextColumn();
            ImGui::Text("%s", s->desc().c_str());
        }
        ImGui::EndTable();
    }
} // namespace dnd::graphic::widget
