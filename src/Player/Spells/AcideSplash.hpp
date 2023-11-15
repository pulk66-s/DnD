#pragma once

#include "../PlayerNamespace.hpp"
#include "ASpell.hpp"

namespace dnd::player::spells
{
    class AcideSplash : public ASpell {
    public:
        AcideSplash(): ASpell("Acide Splash", "A splash of acide", 0) {};
    };
} // namespace dnd::player::spells
