#pragma once

#include "../ObjectNamespace.hpp"
#include "AItem.hpp"
#include "../../Player/Dice.hpp"

namespace dnd::objects::items
{
    class Weapon : public AItem {
    protected:
        player::Dice *_damages;
        int maxWeapons = 4;
    public:
        Weapon(
            std::string name = "Unknown",
            player::Dice *damages = new player::Dice()
        ): AItem(name), _damages(damages) {};
        player::Dice *damages() const { return this->_damages; };
        void damages(player::Dice *d) { this->_damages = d; };
    };
} // namespace dnd::objects::items
