#pragma once

#include "PlayerNamespace.hpp"
#include <unordered_map>
#include <string>
#include <algorithm>

namespace dnd::player
{
    class Inventory {
    private:
        std::unordered_map<std::string, int> _inv = {
            {"element", 1}
        };
    public:
        void addElement(std::string key, int value) {
            if (this->_inv.find(key) == this->_inv.end()) {
                this->_inv[key] = value;
            } else {
                this->_inv[key] += value;
                if (this->_inv[key] <= 0) {
                    this->_inv.erase(key);
                }
            }
        }

        std::unordered_map<std::string, int> inv() const { return this->_inv; };
    };
} // namespace dnd::player
