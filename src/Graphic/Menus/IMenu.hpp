#pragma once

#include "../GraphicNamespace.hpp"

namespace dnd::graphic::menus
{
    class IMenu {
    public:
        virtual ~IMenu() = default;
        virtual void display() = 0;
    };
} // namespace dnd::graphic::menus
