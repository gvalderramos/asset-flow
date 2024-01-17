#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "sqlite3.h"
#include "entities.hpp"

class Query;

class Storage {
public:
    Storage(const std::filesystem::path& path);
    ~Storage();

    template <class T>
    std::vector<T> find(const Query& query) const;
    Entity insert(const Entity& entity);
    Entity update(const Query& query, const Entity& entity);
    void remove(const Query& query);

private:
    sqlite3 *m_db;
    std::filesystem::path m_location;

    void open();
    void close();
    void checkMigrations();
};
