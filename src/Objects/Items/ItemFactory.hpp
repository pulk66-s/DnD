#pragma once

#include "../ObjectNamespace.hpp"
#include "Food/Cheese.hpp"
#include "AItem.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

namespace dnd::objects::items
{
    class ItemFactory {
    private:
        std::unordered_map<std::string, std::function<AItem *(void)>> itemFactoryConstructors = {};
    public:
        ItemFactory() {
            this->add("WarHammer", []() { return new WarHammer(); });
            this->add("StandardSword", []() { return new StandardSword(); });
            this->add("Cheese", []() { return new food::Cheese(); });
        }
        AItem *create(std::string name) {
            return itemFactoryConstructors[name]();
        }
        void add(std::string name, std::function<AItem *()> constructor) {
            itemFactoryConstructors[name] = constructor;
        }
        std::vector<std::string> list() {
            std::vector<std::string> list = {};
            for (auto elem : itemFactoryConstructors) {
                list.push_back(elem.first);
            }
            return list;
        }
    };
} // namespace dnd::objects::items
