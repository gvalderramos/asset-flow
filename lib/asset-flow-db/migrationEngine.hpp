#pragma once

#include <map>
#include <functional>

#include "storage.hpp"
#include "migrationTable.hpp"

class MigrationEngine {
public:
    MigrationEngine();
    ~MigrationEngine();

    void addMigration(const int& version, std::function<void(std::shared_ptr<Storage>)> task);
    const int currentVersion() const;
    void execute(std::shared_ptr<Storage> storage, std::vector<int> versions = {});
    std::vector<int> shouldRun(std::shared_ptr<Storage> storage);
private:
    std::map<int, std::function<void(std::shared_ptr<Storage>)>> m_tasks;
};