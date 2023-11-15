#pragma once

#include "../PlayerNamespace.hpp"
#include <string>

namespace dnd::player::spells
{
    class ASpell {
    protected:
        std::string _name = "";
        std::string _desc = "";
        int _level = 0;
    public:
        ASpell(
            std::string name = "Unknown",
            std::string desc = "No description",
            int level = 1
        ): _name(name), _desc(desc), _level(level) {};

        std::string name() const { return this->_name; };
        void name(std::string name) { this->_name = name; };
        std::string desc() const { return this->_desc; };
        void desc(std::string desc) { this->_desc = desc; };
        int level() const { return this->_level; };
        void level(int level) { this->_level = level; };
    };
} // namespace dnd::player::spells
