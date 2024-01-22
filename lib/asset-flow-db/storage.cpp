#include "storage.hpp"
#include "migration.hpp"

#include <stdio.h>
#include <iostream>


std::vector<MigrationEngine> getMigrations() {
    // std::function<void(const Storage& storage)> m1_task1 = &m1_t1;
    auto m1Tasks = std::vector<std::function<void(Storage*)>> {
        [](Storage* storage) -> void {
            Migration m;
            m.version = 1;
            storage->create(Query(Query::QueryMethod::Create, m.getFullSchema()));
            storage->insert(Query(Query::QueryMethod::Insert, "migration(version)").values(std::to_string(m.version.get())));
        },
    };
    MigrationEngine m1(1, m1Tasks);
    std::vector<MigrationEngine> migrationEngines{
        m1,
    };
    return migrationEngines;
}


Storage::Storage(const std::filesystem::path& path)
    : m_location(path), m_migrationEngine(getMigrations())
{
    if (!std::filesystem::exists(m_location.parent_path())) {
        std::filesystem::create_directories(m_location.parent_path());
    }
    if(open() != SQLITE_OK) {
        std::cerr << "Error while opening the database! ERROR: " << exit << std::endl;
        throw("Error while opening the database!");
    }
    checkMigrations();
}

Storage::~Storage() {
    close();
}

int Storage::open() {
    return sqlite3_open(m_location.string().c_str(), &m_db);
}

void Storage::close() {
    // sqlite3_finalize(m_stmt);
    sqlite3_close(m_db);
}

void Storage::checkMigrations() {
    for(auto& m : m_migrationEngine) {
        if(m.shouldRun(this)) {
            m.execute(this);
        }
    }
}

int Storage::updateStmt(const char* zSql, sqlite3_stmt* stmt){
    return sqlite3_prepare_v2(m_db, zSql, -1, &stmt, nullptr);
}

void Storage::insert(const Query& query) {
    auto sqlStr = query.str();
    int exit = 0;
    char* messageError;
    exit = sqlite3_exec(m_db, sqlStr.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error in createTable function." << std::endl;
        sqlite3_free(messageError);
    }
    else
        std::cout << "Table created Successfully" << std::endl;
}
void Storage::update(const Query& query) {
    auto sqlStr = query.str();
    int exit = 0;
    char* messageError;
    exit = sqlite3_exec(m_db, sqlStr.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error in createTable function." << std::endl;
        sqlite3_free(messageError);
    }
    else
        std::cout << "Table created Successfully" << std::endl;
}
void Storage::remove(const Query& query) {
    auto sqlStr = query.str();
    int exit = 0;
    char* messageError;
    exit = sqlite3_exec(m_db, sqlStr.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error in createTable function." << std::endl;
        sqlite3_free(messageError);
    }
    else
        std::cout << "Table created Successfully" << std::endl;
}
void Storage::create(const Query& query) {
    auto sqlStr = query.str();
    int exit = 0;
    char* messageError;
    exit = sqlite3_exec(m_db, sqlStr.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error in createTable function." << std::endl;
        sqlite3_free(messageError);
    }
    else
        std::cout << "Table created Successfully" << std::endl;
}