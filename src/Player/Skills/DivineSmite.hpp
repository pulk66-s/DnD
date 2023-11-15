#pragma once

#include "../PlayerNamespace.hpp"
#include "ASkill.hpp"

namespace dnd::player::skills
{
    class DivineSmite : public ASkill {
    public:
        DivineSmite(): ASkill("Divine Smite", "You can expend one spell slot to deal radiant damage to the target, in addition to the weapon's damage. The extra damage is 2d8 for a 1st-level spell slot, plus 1d8 for each spell level higher than 1st, to a maximum of 5d8. The damage increases by 1d8 if the target is an undead or a fiend.") {};
    };
} // namespace dnd::player::skills
