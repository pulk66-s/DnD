/**
 * @brief   This describe the current namespace of all the user's classes.
*/

namespace dnd::player
{
    class Player;
    class Inventory;
    class Dice;
    namespace pclass {
        class IClass;
        class AClass;
        class Paladin;
        class Fighter;
    } // namespace dnd::player::pclass
    namespace spells
    {
        class ASpell;
        class FireBall;
        class AcideSpell;
    } // namespace spells
    namespace skills
    {
        class ASkill;
        class DivineSmite;
    } // namespace skills
    namespace data {
        class Money;
        class DiceStats;
        class Stats;
        class Skills;
        class Equipment;
    }
} // namespace dnd::user
