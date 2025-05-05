#include "MetadataManager.h"
#include <fstream>

bool MetadataManager::createTable(const std::string& tableName, const std::vector<std::string>& columns) {
    schema[tableName] = columns;
    std::ofstream metaFile("data/" + tableName + "_meta.txt");
    for (const auto& col : columns) {
        metaFile << col << ",";
    }
    metaFile << std::endl;
    return true;
}

std::vector<std::string> MetadataManager::getTableSchema(const std::string& tableName) {
    return schema[tableName];
}