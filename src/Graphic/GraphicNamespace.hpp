#pragma once

namespace dnd::graphic
{
    namespace menus
    {
        class IMenu;
        class AMenu;
        class MainMenu;
        class MenuFactory;
        class ClassMenu;
    } // namespace menu

    namespace widget
    {
        class AWidget;
        class WidgetFactory;
        class ClassWidget;
        class PlayerWidget;
        class SpellWidget;
        class SkillWidget;

        namespace wplayer
        {
            class Inventory;
            class Money;
            class Weapon;
            class Stats;
            class SavingThrows;
            class Spells;
            class Skills;
        } // namespace player
        
    } // namespace widget
    
} // namespace dnd::graphic
