#pragma once

#include "../ObjectNamespace.hpp"
#include "Armor.hpp"

namespace dnd::objects::items
{
    class StandardArmor : public Armor {
    public:
        StandardArmor(): Armor("Standard armor", 20) {};
    };
} // namespace dnd::objects::items
