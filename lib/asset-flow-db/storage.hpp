#pragma once

#include <string>
#include <filesystem>
#include <iostream>

#include <sqlite3.h>
#include <spdlog/spdlog.h>

#include "query.hpp"


class Storage {
public:
    Storage() = delete;
    Storage(const std::filesystem::path& path) : m_path(path) {};
    Storage(const Storage& other) {m_path = other.m_path;};
    ~Storage() {};

    void interact(const Query& query, std::function<void(sqlite3_stmt*)> callback);
    void interact(const Query& query);
private:
    std::filesystem::path m_path;
};
