#pragma once

#include "../Spells/Fireball.hpp"
#include "../Spells/AcideSplash.hpp"
#include "../PlayerNamespace.hpp"
#include <vector>
#include <algorithm>

namespace dnd::player::data
{
    class Spells {
    private:
        std::vector<spells::ASpell *> spells = {
            new spells::Fireball(),
            new spells::AcideSplash()
        };
        int spellsLimits[10] = {0};
        int castedSpells[10] = {0};
    public:
        Spells() {
            for (int i = 0; i < 10; i++) {
                this->spellsLimits[i] = 0;
                this->castedSpells[i] = 0;
            }
        }
        void add(spells::ASpell *spell) {
            this->spells.push_back(spell);
        }
        void set(std::vector<spells::ASpell *> spells) {
            this->spells = spells;
        }
        std::vector<spells::ASpell *> list() {
            return this->spells;
        }
        void remove(spells::ASpell *spell) {
            this->spells.erase(
                std::remove_if(
                    this->spells.begin(), this->spells.end(), 
                    [spell](spells::ASpell *s) {return s == spell;}
                ), this->spells.end()
            );
        }
        std::vector<int> limits() {
            std::vector<int> limits;
            for (int i = 0; i < 10; i++) {
                limits.push_back(this->spellsLimits[i]);
            }
            return limits;
        }
        int limit(int level) {
            return this->spellsLimits[level];
        }
        bool cast(int level) {
            if (this->castedSpells[level] < this->spellsLimits[level]) {
                this->castedSpells[level]++;
                return true;
            }
            return false;
        }
        int casted(int level) {
            return this->castedSpells[level];
        }
    };
} // namespace dnd::player::data
