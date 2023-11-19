#pragma once

#include "PlayerNamespace.hpp"
#include "Class/Paladin.hpp"
#include "Class/AClass.hpp"
#include "Inventory.hpp"
#include "../Objects.hpp"
#include "../Lib/Json.hpp"
#include <string>
#include "PlayerData/Money.hpp"
#include "PlayerData/DiceStats.hpp"
#include "PlayerData/Equipment.hpp"
#include "PlayerData/Skills.hpp"
#include "PlayerData/Spells.hpp"
#include "PlayerData/Stats.hpp"

namespace dnd::player
{
    class Player {
    private:
        Inventory _inv;
        std::string _name = "";
        std::string _desc = "";
        pclass::AClass *_class = nullptr;
        data::Money playerMoney;
        data::DiceStats playerDiceStats;
        data::Equipment playerEquipment;
        data::Skills playerSkills;
        data::Spells playerSpells;
        data::Stats playerStats;
    public:
        Player(
            std::string name = "Unknown", 
            std::string desc = "No description", 
            pclass::AClass *c = new pclass::Paladin()
        ): _name(name), _desc(desc), _class(c) {};
        Player(nlohmann::json json) {
            this->_name = json["name"];
            this->_desc = json["desc"];
            if (json["class"] == "Paladin") {
                this->_class = new pclass::Paladin();
            } else {
                this->_class = new pclass::AClass();
            }
            // this->_class = pclass::AClass::getClass(json["class"]);
            this->playerStats.level(json["level"]);
            this->playerStats.hp(json["hp"]);
            this->playerStats.maxHp(json["maxHp"]);
            this->playerStats.proficiency(json["proficiency"]);
            this->playerStats.alignment(json["alignment"]);
            this->playerMoney.set(json["coins"]);
            this->playerDiceStats.setSaving(json["saving"]);
            this->playerDiceStats.set(json["stats"]);
            // this->_weapons = json["weapons"];
            // this->_armor = json["armor"];
            // this->_skills = json["skills"];
            // this->_spells = json["spells"];
        }

        std::string name() const { return this->_name; };
        void name(std::string name) { this->_name = name; };
        std::string desc() const { return this->_desc; };
        void desc(std::string desc) { this->_desc = desc; };
        pclass::AClass *pclass() const { return this->_class; };
        void pclass(pclass::AClass *c) { this->_class = c; };
        data::DiceStats diceStats() const { return this->playerDiceStats; };
        Inventory *inv() { return &this->_inv; };
        data::Money &money() { return this->playerMoney; };
        data::Skills skills() { return this->playerSkills; };
        data::Equipment equipment() { return this->playerEquipment; };
        data::Stats stats() { return this->playerStats; };
        data::Spells spells() { return this->playerSpells; };

        void saveJson() {
            lib::json::Json json("files/players/" + this->_name + ".json");

            json.set("name", this->_name);
            json.set("desc", this->_desc);
            json.set("class", this->_class->name());
            json.set("level", this->playerStats.level());
            json.set("hp", this->playerStats.hp());
            json.set("maxHp", this->playerStats.maxHp());
            json.set("proficiency", this->playerStats.proficiency());
            json.set("alignment", this->playerStats.alignment());
            json.set("coins", this->playerMoney.get());
            json.set("saving", this->playerDiceStats.getSaving());
            json.set("stats", this->playerDiceStats.get());
            // json.set("weapons", this->_weapons);
            // json.set("armor", this->_armor);
            // json.set("skills", this->_skills);
            // json.set("spells", this->_spells);
            json.save();
        }
        bool exists() {
            lib::json::Json json("files/players/" + this->_name + ".json");

            return json.exists();
        }
    };
} // namespace dnd::player
