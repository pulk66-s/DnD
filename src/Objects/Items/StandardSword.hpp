#pragma once

#include "../ObjectNamespace.hpp"
#include "Weapon.hpp"
#include "../../Player/Dice.hpp"

namespace dnd::objects::items
{
    class StandardSword : public Weapon {
    public:
        StandardSword(): Weapon("Standard sword", new player::Dice(1, 6)) {};
    };
} // namespace dnd::objects::items
