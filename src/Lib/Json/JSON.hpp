#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>
#include "../LibNamespace.hpp"

namespace dnd::lib::json
{
    class Json {
    private:
        nlohmann::json json;
        std::string _path;
    public:
        Json(std::string path = ""): _path(path) {}
        nlohmann::json& get() { return json; }
        std::string path() { return _path; }
        void path(std::string path) { _path = path; }
        void load() {
            std::ifstream file(_path);
            if (file.is_open()) {
                file >> json;
                file.close();
            }
        }
        bool exists() {
            std::ifstream file(_path);
            return file.is_open();
        }
        void create() {
            std::ofstream file(_path);
            file << "{}";
            file.close();
        }
        void save() {
            std::ofstream file(_path);
            file << json.dump(4);
            file.close();
        }
        void set(std::string key, nlohmann::json value) {
            json[key] = value;
        }
        static std::vector<std::string> listsFiles(std::string folder) {
            std::vector<std::string> files = {};
            for (const auto & entry : std::filesystem::directory_iterator(folder)) {
                files.push_back(entry.path().filename().string());
            }
            return files;
        }
    };
} // namespace dnd::lib::json
