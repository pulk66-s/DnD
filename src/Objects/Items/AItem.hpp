#pragma once

#include "../ObjectNamespace.hpp"
#include <string>

namespace dnd::objects::items
{
    class AItem {
    protected:
        std::string _name = "";
        std::string _desc = "";
    public:
        AItem(
            std::string name = "Unknown",
            std::string desc = "No description"
        ): _name(name), _desc(desc) {};
        std::string name() const { return this->_name; };
        void name(std::string name) { this->_name = name; };
        std::string desc() const { return this->_desc; };
        void desc(std::string desc) { this->_desc = desc; };
    };
} // namespace dnd::objects::items
