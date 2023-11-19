#pragma once

#include "../PlayerNamespace.hpp"
#include <string>
#include <unordered_map>

namespace dnd::player::data
{
    class DiceStats {
    public:
        enum PlayerStats {
            STR,
            DEX,
            CON,
            INT,
            WIS,
            CHA
        };
        static std::string toString(PlayerStats e) {
            switch (e) {
                case STR: return "STR";
                case DEX: return "DEX";
                case CON: return "CON";
                case INT: return "INT";
                case WIS: return "WIS";
                case CHA: return "CHA";
            }
            return "UNKNOWN";
        }
        void add(PlayerStats stat, int amount) {
            _stats[stat].first += amount;
        }
        void set(PlayerStats stat, int amount) {
            _stats[stat].first = amount;
        }
        void set(std::unordered_map<PlayerStats, std::pair<int, int>> stats) {
            _stats = stats;
        }
        int get(PlayerStats stat) {
            return _stats[stat].first;
        }
        std::unordered_map<PlayerStats, std::pair<int, int>> get() {
            return _stats;
        }
        void remove(PlayerStats stat, int amount) {
            _stats[stat].first -= amount;
        }
        void addSaving(PlayerStats stat, bool amount) {
            _saving[stat] = amount;
        }
        void setSaving(PlayerStats stat, bool amount) {
            _saving[stat] = amount;
        }
        void setSaving(std::unordered_map<PlayerStats, bool> stats) {
            _saving = stats;
        }
        bool getSaving(PlayerStats stat) {
            return _saving[stat];
        }
        std::unordered_map<PlayerStats, bool> getSaving() {
            return _saving;
        }
        void removeSaving(PlayerStats stat, bool amount) {
            _saving[stat] = amount;
        }
    private:
        std::unordered_map<PlayerStats, std::pair<int, int>> _stats = {
            {STR, {0, 0}},
            {DEX, {0, 0}},
            {CON, {0, 0}},
            {INT, {0, 0}},
            {WIS, {0, 0}},
            {CHA, {0, 0}}
        };
        std::unordered_map<PlayerStats, bool> _saving = {
            {STR, false},
            {DEX, false},
            {CON, false},
            {INT, false},
            {WIS, false},
            {CHA, false}
        };
    };
} // namespace dnd::player::data
