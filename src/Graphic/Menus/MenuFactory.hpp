#pragma once

#include "../GraphicNamespace.hpp"
#include "MainMenu.hpp"
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

namespace dnd::graphic::menus
{
    static std::unordered_map<std::string, std::function<AMenu *(void)>> constructors;
    class MenuFactory {
    public:
        static void initFactory() {
            constructors = {};
            MenuFactory::add("MainMenu", []() { return new MainMenu(); });
        }

        static AMenu *create(const std::string &name) {
            return constructors[name]();
        }

        static void add(const std::string &name, std::function<AMenu *(void)> constructor) {
            constructors[name] = constructor;
        }
    };
} // namespace dnd::graphic::menus
