#pragma once

#include "storage.hpp"

template <>
std::vector<Migration> Storage::find(const Query& query) {
    auto it = ENTITIES.find(query.tableName());
    Entities entityName;
    if (it != ENTITIES.end()) {
        entityName = it->second;
    } else {
        std::cerr << "Unable to find the table name: " << query.tableName() << std::endl;
    }

    if (entityName != Entities::Migration) {
        std::cerr << "Quering the wrong table. Expecting 'migration' get: " << query.tableName() << std::endl;
    }

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(m_db, query.str().c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error while starting sqlite3 statement." << std::endl;
    }
    std::vector<Migration> result;
    // FIXME: not finding table... 
    auto step = sqlite3_step(stmt);

    while(step == SQLITE_ROW) {
        auto numCols = sqlite3_column_count(stmt);
        if(numCols <= 0) {
            break;
        }
        Migration m;
        m.id = sqlite3_column_int(stmt, 0);
        m.version = sqlite3_column_int(stmt, 1);
        result.push_back(m);

        step = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    return result;
};