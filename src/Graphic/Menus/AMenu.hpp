#pragma once

#include "../GraphicNamespace.hpp"
#include "IMenu.hpp"
#include "../Widget/AWidget.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

namespace dnd::graphic::menus
{
    class AMenu : public IMenu {
    protected:
        std::string _title;
        std::vector<widget::AWidget *> _widgets = {};

        // Private constructor to prevent instantiation
        AMenu(std::string title = "Unknown") : _title(title) {}
    public:
        void display() {
            // std::cout << "start" << std::endl;
            for (widget::AWidget *widget : this->_widgets) {
                if (widget != nullptr) {
                    // std::cout << "widget" << std::endl;
                    widget->display();
                } else {
                    // std::cout << "widget is null" << std::endl;
                }
            }
            // std::cout << "end" << std::endl;
        }

        std::string title() const { return this->_title; };
        void title(std::string title) { this->_title = title; };

        friend std::ostream &operator<<(std::ostream& os, const AMenu& m) {
            os << "Menu: " << std::endl << "\ttitle: " << m._title;
            return os;
        };

        void addWidget(widget::AWidget *widget) {
            this->_widgets.push_back(widget);
        }
    };
} // namespace dnd::graphic::menus
