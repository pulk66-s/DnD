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
        class CreatePlayerWidget;
        class LoadPlayerWidget;
        class ItemWidget;

        namespace wplayer
        {
            class Inventory;
            class Money;
            class Weapon;
            class Stats;
            class SavingThrows;
            class Spells;
            class Skills;
            class Actions;
        } // namespace player
        
    } // namespace widget
    
} // namespace dnd::graphic
