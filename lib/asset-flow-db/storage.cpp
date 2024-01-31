#include "storage.hpp"


void Storage::interact(const Query& query, std::function<void(sqlite3_stmt*)> callback) {
    spdlog::set_level(spdlog::level::debug);
    int exit = 0;
    sqlite3* db;
    exit = sqlite3_open(m_path.string().c_str(), &db);
    if (exit != SQLITE_OK) {
        spdlog::critical("Error while opening connection with the database.");
        sqlite3_close(db);
    }
    spdlog::debug("Storage opened successfully");

    sqlite3_stmt *stmt;
    auto sqlStr = query.str();
    spdlog::debug("Searching sql {0}", sqlStr);
    exit = sqlite3_prepare_v3(db, sqlStr.c_str(), -1, SQLITE_PREPARE_PERSISTENT, &stmt, nullptr);
    if (exit != SQLITE_OK) {
        spdlog::critical("Error while starting sqlite3 statement.");
    } else {
        spdlog::debug("Calling external function...");
        callback(stmt);
        spdlog::debug("Function called successfully.");
    }
    
    spdlog::debug("Closing database connection.");
    if (sqlite3_finalize(stmt) != SQLITE_OK || sqlite3_close(db) != SQLITE_OK) {
        spdlog::critical("Error while closing connection with the database.");
    }
}

void Storage::interact(const Query& query) {
    spdlog::set_level(spdlog::level::debug);
    int exit = 0;
    sqlite3* db;
    exit = sqlite3_open(m_path.string().c_str(), &db);
    if (exit != SQLITE_OK) {
        spdlog::critical("Error while opening connection with the database.");
        sqlite3_close(db);
    }
    spdlog::debug("Storage opened successfully");

    auto sqlStr = query.str();
    spdlog::debug("Searching sql {0}", sqlStr);
    char* messageError;
    exit = sqlite3_exec(db, sqlStr.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        spdlog::critical("Error while starting sqlite3 statement, because {}", messageError);
    } 
    sqlite3_free(messageError);
    spdlog::debug("Closing database connection.");
    if (sqlite3_close(db) != SQLITE_OK) {
        spdlog::critical("Error while closing connection with the database.");
    }
}