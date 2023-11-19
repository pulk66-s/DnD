#pragma once

#include "../PlayerNamespace.hpp"
#include "../../Objects.hpp"
#include "../Spells/Fireball.hpp"
#include "../Spells/AcideSplash.hpp"
#include "../Skills/ASkill.hpp"
#include "../Skills/DivineSmite.hpp"
#include <vector>

namespace dnd::player::data
{
    class Skills {
    private:
        std::vector<skills::ASkill *> _skills = {
            new skills::DivineSmite(),
            new skills::DivineSmite()
        };
        std::vector<spells::ASpell *> _spells = {
            new spells::Fireball(),
            new spells::AcideSplash()
        };
    public:
        void addSkill(skills::ASkill *skill) {
            this->_skills.push_back(skill);
        }
        void skills(std::vector<skills::ASkill *> skills) {
            this->_skills = skills;
        }
        std::vector<skills::ASkill *> skills() {
            return this->_skills;
        }
        void removeSkill(skills::ASkill *skill) {
            this->_skills.erase(
                std::remove_if(
                    this->_skills.begin(), this->_skills.end(), 
                    [skill](skills::ASkill *s) {return s == skill;}
                ), this->_skills.end()
            );
        }
        void addSpell(spells::ASpell *spell) {
            this->_spells.push_back(spell);
        }
        void spells(std::vector<spells::ASpell *> spells) {
            this->_spells = spells;
        }
        std::vector<spells::ASpell *> spells() {
            return this->_spells;
        }
        void removeSpell(spells::ASpell *spell) {
            this->_spells.erase(
                std::remove_if(
                    this->_spells.begin(), this->_spells.end(), 
                    [spell](spells::ASpell *s) {return s == spell;}
                ), this->_spells.end()
            );
        }
    };
} // namespace dnd::player::data
