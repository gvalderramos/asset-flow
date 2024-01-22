#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <functional>

#include "sqlite3.h"
#include "entities.hpp"
#include "query.hpp"
// #include "migration.hpp"

class MigrationEngine;

class Storage {
public:
    Storage(const std::filesystem::path& path);
    ~Storage();

    template <class T>
    std::vector<T> find(const Query& query);

    void insert(const Query& query);
    void update(const Query& query);
    void remove(const Query& query);
    void create(const Query& query);

private:
    sqlite3 *m_db;
    // sqlite3_stmt* m_stmt;
    std::filesystem::path m_location;
    std::vector<MigrationEngine> m_migrationEngine;

    int open();
    void close();
    void checkMigrations();
    int updateStmt(const char* zSql, sqlite3_stmt* stmt);
};
