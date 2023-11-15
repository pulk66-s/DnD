#pragma once

#include "../ObjectNamespace.hpp"
#include "AItem.hpp"

namespace dnd::objects::items
{
    class Armor : public AItem {
    protected:
        int _ca = 0;
    public:
        Armor(std::string name, int res): AItem(name), _ca(res) {};
        int ca() const { return this->_ca; };
        void ca(int ca) { this->_ca = ca; };
    };
} // namespace dnd::objects::items
