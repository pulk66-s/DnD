#pragma once

#include "PlayerNamespace.hpp"
#include "../Objects.hpp"
#include <unordered_map>
#include <string>
#include <algorithm>

namespace dnd::player
{
    class Inventory {
    private:
        std::unordered_map<objects::items::AItem *, int *> _inv = {
            {new objects::items::food::Cheese(), new int(1)}
        };
    public:
        Inventory() {
            this->addElement(new objects::items::food::Cheese(), 2);
        };
        void addElement(objects::items::AItem *key, int value) {
            auto it = std::find_if(this->_inv.begin(), this->_inv.end(), [key](std::pair<objects::items::AItem *, int *> elem) {
                return elem.first->name() == key->name();
            });
            if (it != this->_inv.end()) {
                *it->second += value;
            } else {
                this->_inv[key] = new int(value);
            }
        }
        void setElement(objects::items::AItem *key, int value) {
            this->_inv[key] = new int(value);
        }
        void clean() {
            this->_inv.erase(
                std::find_if(
                    this->_inv.begin(),
                    this->_inv.end(),
                    [](std::pair<objects::items::AItem *, int *> elem) {
                        return *elem.second <= 0;
                    }
                ),
                this->_inv.end()
            );
        }
        std::unordered_map<objects::items::AItem *, int *> inv() const { return this->_inv; };
    };
} // namespace dnd::player
