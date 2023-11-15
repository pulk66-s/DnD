#pragma once

#include "../PlayerNamespace.hpp"
#include "ASpell.hpp"

namespace dnd::player::spells
{
    class Fireball : public ASpell {
    public:
        Fireball(): ASpell("Fireball", "A fireball is a big ball of fire", 3) {};
    };
} // namespace dnd::player::spells
