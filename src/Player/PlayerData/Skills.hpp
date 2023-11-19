#pragma once

#include "../PlayerNamespace.hpp"
#include "../../Objects.hpp"
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
    };
} // namespace dnd::player::data
