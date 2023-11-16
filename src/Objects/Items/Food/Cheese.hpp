#pragma once

#include "../../ObjectNamespace.hpp"
#include "../Food.hpp"

namespace dnd::objects::items::food
{
    class Cheese : public Food {
    public:
        Cheese(): Food("Cheese", "A piece of cheese") {};
    };
} // namespace dnd::objects::items::food
