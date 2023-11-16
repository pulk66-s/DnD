#pragma once

#include "../PlayerNamespace.hpp"
#include "IClass.hpp"
#include <string>
#include <vector>
#include <sstream>

namespace dnd::player::pclass
{
    struct ClassTableLine {
        int level;
        int proficiencyBonus;
        std::vector<std::string> features;
        std::vector<int> spellSlots;
    };

    class AClass : public IClass {
    protected:
        std::string _name = "";
        std::string _desc = "";
        std::vector<ClassTableLine> _table = {};

        // Protected constructor to prevent instantiation of this class

    public:
        AClass(
            std::string name = "Unknown",
            std::string desc = "No description"
        ) : _name(name) { };
        std::string name() const { return this->_name; };
        void name(std::string name) { this->_name = name; };
        std::string desc() const { return this->_desc; };
        void desc(std::string desc) { this->_desc = desc; };
        std::vector<ClassTableLine> table() const { return this->_table; };
        void table(std::vector<ClassTableLine> table) { this->_table = table; };

        // Overload of the << operator to print the class name
        friend std::ostream &operator<<(std::ostream& os, const AClass& c) {
            os << "Class: " << std::endl << "\tname: " << c._name;
            return os;
        };
    };
} // namespace dnd::player::pclass
