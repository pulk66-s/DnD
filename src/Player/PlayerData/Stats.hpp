#pragma once

#include "../PlayerNamespace.hpp"
#include <string>

namespace dnd::player::data
{
    class Stats {
    private:
        int _level = 1;
        int _proficiency = 2;
        int _maxHp = 0;
        int _hp = 0;
        std::string _alignment = "N";
    public:
        int level() {
            return this->_level;
        }
        void level(int level) {
            this->_level = level;
        }
        int proficiency() {
            return this->_proficiency;
        }
        void proficiency(int proficiency) {
            this->_proficiency = proficiency;
        }
        int maxHp() {
            return this->_maxHp;
        }
        void maxHp(int maxHp) {
            this->_maxHp = maxHp;
        }
        int hp() {
            return this->_hp;
        }
        void hp(int hp) {
            this->_hp = hp;
        }
        std::string alignment() {
            return this->_alignment;
        }
        void alignment(std::string alignment) {
            this->_alignment = alignment;
        }
        
    };
} // namespace dnd::player::data
