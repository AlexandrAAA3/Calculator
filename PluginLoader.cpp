#include "NodeParser.h"
#include <windows.h>
#include <filesystem>
#include <iostream>

void loadPlugins(const std::string &folderPath) {
    if (!std::filesystem::exists(folderPath) || !std::filesystem::is_directory(folderPath)) {
        std::cerr << "Warning: Folder " << folderPath << " not found.\n";
        return;
    }

    for (const auto &entry: std::filesystem::directory_iterator(folderPath)) {
        // поиск dll
        if (entry.path().extension() != ".dll")
            continue;

        std::string path = entry.path().string();

        // загрузка dll
        HMODULE hMod{LoadLibraryA(path.c_str())};
        if (!hMod) {
            std::cerr << "Error: Cannot load dll: " << path << "\n";
            continue;
        }

        auto getName{(const char*(*)()) GetProcAddress(hMod, "get_name")};
        auto evaluate{(double(*)(double)) GetProcAddress(hMod, "evaluate")};

        if (!getName || !evaluate) {
            std::cerr << "Error: Invalid dll (no required exports): " << path << "\n";
            FreeLibrary(hMod);
            continue;
        }

        // получение и запись имени в таблицу
        std::string name{getName()};
        functionTable[name] = evaluate;

        std::cout << "Loaded plugin: " << name << "\n";
    }
}
