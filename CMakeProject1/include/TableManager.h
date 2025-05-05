#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class TableManager {
private:
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> data;
public:
    bool insertRow(const std::string& tableName, const std::vector<std::string>& values);
    std::vector<std::vector<std::string>> selectRows(const std::string& tableName);
};