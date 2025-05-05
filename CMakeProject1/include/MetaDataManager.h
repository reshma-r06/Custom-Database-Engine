#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class MetadataManager {
private:
    std::unordered_map<std::string, std::vector<std::string>> schema;
public:
    bool createTable(const std::string& tableName, const std::vector<std::string>& columns);
    std::vector<std::string> getTableSchema(const std::string& tableName);
};