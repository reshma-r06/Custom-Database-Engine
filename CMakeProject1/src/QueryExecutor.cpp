#include "QueryExecutor.h"
#include <iostream>
#include <sstream>
#include <algorithm>

void QueryExecutor::run() {
    std::string input;
    std::cout << "Mini DBMS Ready. Type your query (or type EXIT):\n";

    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);
        if (input == "EXIT") break;

        if (input.find("CREATE TABLE") == 0) {
            createTable(input);
        }
        else if (input.find("INSERT INTO") == 0) {
            insertIntoTable(input);
        }
        else if (input.find("SELECT * FROM") == 0) {
            selectFromTable(input);
        }
        else {
            std::cout << "Invalid command.\n";
        }
    }
}

void QueryExecutor::createTable(const std::string& input) {
    std::istringstream iss(input);
    std::string command, tableName, columnList;

    iss >> command >> command >> tableName;
    std::getline(iss, columnList);

    auto start = columnList.find('(');
    auto end = columnList.find(')');
    if (start == std::string::npos || end == std::string::npos) {
        std::cout << "Invalid syntax.\n";
        return;
    }

    columnList = columnList.substr(start + 1, end - start - 1);
    Table table;
    table.columns = tokenize(columnList, ',');

    for (auto& col : table.columns) {
        col.erase(std::remove_if(col.begin(), col.end(), isspace), col.end());
    }

    tables[tableName] = table;
    std::cout << "Table '" << tableName << "' created.\n";
}

void QueryExecutor::insertIntoTable(const std::string& input) {
    std::istringstream iss(input);
    std::string command, into, tableName, valuesKeyword, valueList;

    iss >> command >> into >> tableName >> valuesKeyword;
    std::getline(iss, valueList);

    auto start = valueList.find('(');
    auto end = valueList.find(')');
    if (start == std::string::npos || end == std::string::npos) {
        std::cout << "Invalid syntax.\n";
        return;
    }

    valueList = valueList.substr(start + 1, end - start - 1);
    auto values = tokenize(valueList, ',');

    for (auto& val : values) {
        val.erase(std::remove_if(val.begin(), val.end(), isspace), val.end());
    }

    if (tables.find(tableName) == tables.end()) {
        std::cout << "Table not found.\n";
        return;
    }

    if (values.size() != tables[tableName].columns.size()) {
        std::cout << "Column count mismatch.\n";
        return;
    }

    tables[tableName].rows.push_back(values);
    std::cout << "1 row inserted into '" << tableName << "'.\n";
}

void QueryExecutor::selectFromTable(const std::string& input) {
    std::istringstream iss(input);
    std::string select, star, from, tableName;
    iss >> select >> star >> from >> tableName;

    if (tables.find(tableName) == tables.end()) {
        std::cout << "Table not found.\n";
        return;
    }

    auto& table = tables[tableName];
    for (auto& col : table.columns) std::cout << col << "\t";
    std::cout << "\n";

    for (auto& row : table.rows) {
        for (auto& val : row) std::cout << val << "\t";
        std::cout << "\n";
    }
}

std::vector<std::string> QueryExecutor::tokenize(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string tok;
    while (std::getline(ss, tok, delimiter)) {
        tokens.push_back(tok);
    }
    return tokens;
}
