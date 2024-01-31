#include "database.hpp"


Database::Database(const std::filesystem::path location)
    : m_storage(std::shared_ptr<Storage>(new Storage(location))),
      m_migrationTable(std::shared_ptr<MigrationTable>(new MigrationTable(m_storage))),
      m_assetTable(std::shared_ptr<AssetTable>(new AssetTable(m_storage))),
      m_migrationEngine(MigrationEngine())
{
    addMigration();
    checkMigrationsTask();
}

Database::~Database()
{

}

void Database::addMigration()
{
    m_migrationTable->create();
    m_assetTable->create();

    m_migrationEngine.addMigration(
        1, 
        [&](std::shared_ptr<Storage> storage) -> void {
            auto migrationData =  MigrationTable::Data(1);
            m_migrationTable->insert(migrationData);
        }
    );
}

void Database::checkMigrationsTask()
{
    if(auto versions = m_migrationEngine.shouldRun(m_storage); versions.size()) {
        m_migrationEngine.execute(m_storage, versions);
    }
}