#pragma once

#include "../PlayerNamespace.hpp"
#include "../../Objects.hpp"
#include <vector>

namespace dnd::player::data
{
    class Equipment {
    private:
        std::vector<objects::items::Weapon *> _weapons = {
            new objects::items::StandardSword(),
            new objects::items::WarHammer()
        };
        objects::items::Armor *_armor = new objects::items::StandardArmor();
    public:
        std::vector<objects::items::Weapon *> weapons() {
            return this->_weapons;
        }
        void weapons(std::vector<objects::items::Weapon *> weapons) {
            this->_weapons = weapons;
        }
        void addWeapon(objects::items::Weapon *weapon) {
            this->_weapons.push_back(weapon);
        }
        void removeWeapon(objects::items::Weapon *weapon) {
            this->_weapons.erase(
                std::remove_if(
                    this->_weapons.begin(), this->_weapons.end(), 
                    [weapon](objects::items::Weapon *w) {return w == weapon;}
                ), this->_weapons.end()
            );
        }
        objects::items::Armor *armor() {
            return this->_armor;
        }
        void armor(objects::items::Armor *armor) {
            this->_armor = armor;
        }
    };
} // namespace dnd::player::data
