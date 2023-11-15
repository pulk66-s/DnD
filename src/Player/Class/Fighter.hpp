#pragma once

#include "../PlayerNamespace.hpp"
#include "AClass.hpp"
#include <string>

namespace dnd::player::pclass
{
    class Fighter : public AClass {
    public:
        Fighter() : AClass("Fighter") { };
    };
} // namespace dnd::player::pclass
