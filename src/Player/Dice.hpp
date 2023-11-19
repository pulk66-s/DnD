#pragma once

#include "PlayerNamespace.hpp"
#include <string>

namespace dnd::player
{
    class Dice {
        private:
            int nb = 0, value = 0, _bonus = 0;

        public:
            Dice(int nb = 0, int value = 0, int bonus = 0)
                : nb(nb), value(value), _bonus(bonus) {};

            std::string toString() {
                return std::to_string(this->nb) 
                    + "d" + std::to_string(this->value) 
                    + (_bonus < 0 ? "" : "+") + std::to_string(this->_bonus);
            };

            int roll() {
                int result = 0;
                for (int i = 0; i < nb; i++) {
                    result += rand() % value + 1;
                }
                return result + _bonus;
            };
            void bonus(int bonus) { this->_bonus = bonus; };
    };
} // namespace dnd::player
