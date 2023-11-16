#pragma once

#include "PlayerNamespace.hpp"
#include "Class/Paladin.hpp"
#include "Class/AClass.hpp"
#include "Inventory.hpp"
#include "Spells/ASpell.hpp"
#include "Spells/Fireball.hpp"
#include "Spells/AcideSplash.hpp"
#include "Skills/ASkill.hpp"
#include "Skills/DivineSmite.hpp"
#include "../Objects.hpp"
#include "../Lib/Json.hpp"
#include <string>

namespace dnd::player
{
    enum PlayerMoney {
        PC,
        PA,
        PE,
        PO,
        PP,
    };

    static std::string toString(PlayerMoney e) {
        switch (e) {
            case PC: return "PC";
            case PA: return "PA";
            case PE: return "PE";
            case PO: return "PO";
            case PP: return "PP";
        }
        return "UNKNOWN";
    }

    enum PlayerStats {
        STR,
        DEX,
        CON,
        INT,
        WIS,
        CHA
    };

    static std::string toString(PlayerStats e) {
        switch (e) {
            case STR: return "STR";
            case DEX: return "DEX";
            case CON: return "CON";
            case INT: return "INT";
            case WIS: return "WIS";
            case CHA: return "CHA";
        }
        return "UNKNOWN";
    }

    class Player {
    private:
        Inventory inv;
        std::string _alignment = "N";
        std::string _name = "";
        std::string _desc = "";
        pclass::AClass *_class = nullptr;
        std::vector<objects::items::Weapon *> _weapons = {
            new objects::items::StandardSword(),
            new objects::items::WarHammer()
        };
        objects::items::Armor *_armor = new objects::items::StandardArmor();
        int maxWeapons = 4;
        int _level = 1;
        int _proficiency = 2;
        int _maxHp = 0;
        int _hp = 0;
        std::unordered_map<PlayerStats, std::pair<int, int>> _stats = {
            {STR, {0, 0}},
            {DEX, {0, 0}},
            {CON, {0, 0}},
            {INT, {0, 0}},
            {WIS, {0, 0}},
            {CHA, {0, 0}}
        };
        std::unordered_map<PlayerStats, bool> _saving = {
            {STR, false},
            {DEX, false},
            {CON, false},
            {INT, false},
            {WIS, false},
            {CHA, false}
        };
        std::unordered_map<PlayerMoney, int> _coins = {
            {PC, 0},
            {PA, 0},
            {PE, 0},
            {PO, 0},
            {PP, 0}
        };
        std::vector<skills::ASkill *> _skills = {
            new skills::DivineSmite(),
            new skills::DivineSmite()
        };
        std::vector<spells::ASpell *> _spells = {
            new spells::Fireball(),
            new spells::AcideSplash()
        };
    public:
        Player(
            std::string name = "Unknown", 
            std::string desc = "No description", 
            pclass::AClass *c = new pclass::Paladin(), 
            int level = 1
        ) : _name(name), _desc(desc), _class(c), _level(level) {};
        Player(nlohmann::json json) {
            this->_name = json["name"];
            this->_desc = json["desc"];
            if (json["class"] == "Paladin") {
                this->_class = new pclass::Paladin();
            } else {
                this->_class = new pclass::AClass();
            }
            // this->_class = pclass::AClass::getClass(json["class"]);
            this->_level = json["level"];
            this->_hp = json["hp"];
            this->_maxHp = json["maxHp"];
            this->_proficiency = json["proficiency"];
            this->_alignment = json["alignment"];
            this->_coins = json["coins"];
            this->_saving = json["saving"];
            this->_stats = json["stats"];
            // this->_weapons = json["weapons"];
            // this->_armor = json["armor"];
            // this->_skills = json["skills"];
            // this->_spells = json["spells"];
        }

        std::string name() const { return this->_name; };
        std::string desc() const { return this->_desc; };
        pclass::AClass *pclass() const { return this->_class; };
        int level() const { return this->_level; };
        void name(std::string name) { this->_name = name; };
        void desc(std::string desc) { this->_desc = desc; };
        void pclass(pclass::AClass *c) { this->_class = c; };
        void level(int level) { this->_level = level; };
        std::vector<objects::items::Weapon *> weapons() const { return this->_weapons; };
        void weapons(std::vector<objects::items::Weapon *> weapons) { this->_weapons = weapons; };
        void armor(objects::items::Armor *armor) { this->_armor = armor; };
        objects::items::Armor *armor() const { return this->_armor; };
        int proficiency() const { return this->_proficiency; };
        void proficiency(int proficiency) { this->_proficiency = proficiency; };
        int hp() const { return this->_hp; };
        void hp(int hp) { this->_hp = hp; };
        void maxHp(int max) { this->_maxHp = max; };
        int maxHp() const { return this->_maxHp; };
        std::unordered_map<PlayerStats, std::pair<int, int>> stats() const { return this->_stats; };
        void stats(std::unordered_map<PlayerStats, std::pair<int, int>> stats) { this->_stats = stats; };
        Inventory *getInv() { return &this->inv; };
        std::unordered_map<PlayerMoney, int> &coins() { return this->_coins; };
        void coins(std::unordered_map<PlayerMoney, int> money) { this->_coins = money; };
        std::string alignment() const { return this->_alignment; };
        void alignment(std::string align) { this->_alignment = align; };
        std::unordered_map<PlayerStats, bool> saving() const { return this->_saving; };
        void saving(std::unordered_map<PlayerStats, bool> save) { this->_saving = save; };
        std::vector<skills::ASkill *> skills() const { return this->_skills; };
        void skills(std::vector<skills::ASkill *> skills) { this->_skills = skills; };
        std::vector<spells::ASpell *> spells() const { return this->_spells; };
        void spells(std::vector<spells::ASpell *> spells) { this->_spells = spells; };

        void saveJson() {
            lib::json::Json json("files/players/" + this->_name + ".json");

            json.set("name", this->_name);
            json.set("desc", this->_desc);
            json.set("class", this->_class->name());
            json.set("level", this->_level);
            json.set("hp", this->_hp);
            json.set("maxHp", this->_maxHp);
            json.set("proficiency", this->_proficiency);
            json.set("alignment", this->_alignment);
            json.set("coins", this->_coins);
            json.set("saving", this->_saving);
            json.set("stats", this->_stats);
            this->_weapons = {};
            this->_armor = nullptr;
            this->_skills = {};
            this->_spells = {};
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
