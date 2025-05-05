#include "TableManager.h"
#include <fstream>
#include <sstream>
#include <filesystem>

bool TableManager::insertRow(const std::string& tableName, const std::vector<std::string>& values) {
    data[tableName].push_back(values);
    std::ofstream file("data/" + tableName + ".txt", std::ios::app);
    for (const auto& val : values) {
        file << val << ",";
    }
    file << std::endl;
    return true;
}

std::vector<std::vector<std::string>> TableManager::selectRows(const std::string& tableName) {
    std::vector<std::vector<std::string>> result;
    std::ifstream file("data/" + tableName + ".txt");
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string value;
        while (std::getline(ss, value, ',')) {
            if (!value.empty()) row.push_back(value);
        }
        if (!row.empty()) result.push_back(row);
    }
    return result;
}