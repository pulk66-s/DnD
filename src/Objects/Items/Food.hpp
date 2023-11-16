#pragma once

#include "../ObjectNamespace.hpp"
#include "AItem.hpp"

namespace dnd::objects::items
{
    class Food : public AItem {
    public:
        Food(
            std::string name = "Unknown",
            std::string desc = "No description"
        ): AItem(name, desc) {};
    };
} // namespace dnd::objects::items
