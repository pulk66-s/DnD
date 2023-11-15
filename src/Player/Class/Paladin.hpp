#pragma once

#include "../PlayerNamespace.hpp"
#include "AClass.hpp"
#include <string>

#define PALADIN_DESC "Whether sworn before a god's altar and the witness of a priest, in a sacred glade before nature spirits and fey beings, or in a moment of desperation and grief with the dead as the only witness, a paladin's oath is a powerful bond."

namespace dnd::player::pclass
{
    class Paladin : public AClass {
    public:
        Paladin() : AClass("Paladin", PALADIN_DESC) {
            this->_table = {
                {
                    .level = 1,
                    .proficiencyBonus = 2,
                    .features = {
                        "Divine Sense",
                        "Lay on Hands"
                    },
                    .spellSlots = { 0, 0, 0, 0, 0 }
                },
                {
                    .level = 2,
                    .proficiencyBonus = 2,
                    .features = {
                        "Fighting Style",
                        "Spellcasting",
                        "Divine Smite"
                    },
                    .spellSlots = { 2, 0, 0, 0, 0 }
                }
            };
        };
    };
} // namespace dnd::player::pclass

