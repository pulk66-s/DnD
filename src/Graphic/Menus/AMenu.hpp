#pragma once

#include "../GraphicNamespace.hpp"
#include "IMenu.hpp"
#include "../Widget/AWidget.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace dnd::graphic::menus
{
    class AMenu : public IMenu {
    protected:
        std::string _title;
        std::vector<std::pair<widget::AWidget *, bool *>> _widgets = {};

        // Private constructor to prevent instantiation
        AMenu(std::string title = "Unknown") : _title(title) {}
    public:
        void display() {
            for (std::pair<widget::AWidget *, bool *> widget : this->_widgets) {
                if (widget.first != nullptr && widget.second != nullptr && *widget.second) {
                    widget.first->display();
                }
            }
            this->_widgets.erase(std::remove_if(this->_widgets.begin(), this->_widgets.end(), [](std::pair<widget::AWidget *, bool *> widget) {
                if (widget.first != nullptr && widget.second != nullptr && !*widget.second) {
                    delete widget.first;
                    delete widget.second;
                    return true;
                }
                return false;
            }), this->_widgets.end());
        }

        std::string title() const { return this->_title; };
        void title(std::string title) { this->_title = title; };

        friend std::ostream &operator<<(std::ostream& os, const AMenu& m) {
            os << "Menu: " << std::endl << "\ttitle: " << m._title;
            return os;
        };

        void addWidget(widget::AWidget *widget, bool *open = nullptr) {
            this->_widgets.push_back(std::make_pair(widget, open));
        }
    };
} // namespace dnd::graphic::menus
