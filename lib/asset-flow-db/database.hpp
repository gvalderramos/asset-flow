#pragma once

#include <memory>

#include <spdlog/spdlog.h>

#include "storage.hpp"
#include "migrationEngine.hpp"
#include "migrationTable.hpp"
#include "assetTable.hpp"


class Database {
public:
    Database(const std::filesystem::path location);
    ~Database();

    std::shared_ptr<MigrationTable> getMigrationTable() const {return m_migrationTable; };
    std::shared_ptr<AssetTable> getAssetTable() const {return m_assetTable; };
private:
    std::shared_ptr<Storage> m_storage;
    std::shared_ptr<MigrationTable> m_migrationTable;
    std::shared_ptr<AssetTable> m_assetTable;

    MigrationEngine m_migrationEngine;

    void addMigration();
    void checkMigrationsTask();
};