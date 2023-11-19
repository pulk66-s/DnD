#pragma once

#include "../PlayerNamespace.hpp"
#include <string>
#include <unordered_map>

namespace dnd::player::data
{
    class Money {
    public:
        enum MoneyType {
            PC,
            PA,
            PE,
            PO,
            PP,
        };
        static std::string toString(MoneyType e) {
            switch (e) {
                case PC: return "PC";
                case PA: return "PA";
                case PE: return "PE";
                case PO: return "PO";
                case PP: return "PP";
            }
            return "UNKNOWN";
        }
        void add(MoneyType type, int amount) {
            _coins[type] += amount;
        }
        void set(MoneyType type, int amount) {
            _coins[type] = amount;
        }
        void set(std::unordered_map<MoneyType, int> coins) {
            _coins = coins;
        }
        int get(MoneyType type) {
            return _coins[type];
        }
        std::unordered_map<MoneyType, int> get() {
            return _coins;
        }
        void remove(MoneyType type, int amount) {
            _coins[type] -= amount;
        }
    private:
        std::unordered_map<MoneyType, int> _coins = {
            {PC, 0},
            {PA, 0},
            {PE, 0},
            {PO, 0},
            {PP, 0}
        };
    };
} // namespace dnd::player::data
