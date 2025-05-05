#ifndef QUERY_EXECUTOR_H
#define QUERY_EXECUTOR_H

#include <string>
#include <unordered_map>
#include <vector>

class QueryExecutor {
public:
    void run();  // Main loop

private:
    struct Table {
        std::vector<std::string> columns;
        std::vector<std::vector<std::string>> rows;
    };

    std::unordered_map<std::string, Table> tables;

    void createTable(const std::string& input);
    void insertIntoTable(const std::string& input);
    void selectFromTable(const std::string& input);
    std::vector<std::string> tokenize(const std::string& str, char delimiter);
};

#endif
