#pragma once

#include "PlayerNamespace.hpp"
#include <string>

namespace dnd::player
{
    class Dice {
        private:
            int nb = 0, value = 0, bonus = 0;

        public:
            Dice(int nb = 0, int value = 0, int bonus = 0)
                : nb(nb), value(value), bonus(bonus) {};

            std::string toString() {
                return std::to_string(nb) + "d" + std::to_string(value) + "+" + std::to_string(bonus);
            };

            int roll() {
                int result = 0;
                for (int i = 0; i < nb; i++) {
                    result += rand() % value + 1;
                }
                return result + bonus;
            };
    };
} // namespace dnd::player
