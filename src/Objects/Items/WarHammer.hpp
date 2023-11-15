#pragma once

#include "../ObjectNamespace.hpp"
#include "Weapon.hpp"
#include "../../Player/Dice.hpp"

namespace dnd::objects::items
{
    class WarHammer : public Weapon {
    public:
        WarHammer(): Weapon("WarHammer", new player::Dice(1, 8)) {};
    };
} // namespace dnd::objects::items
