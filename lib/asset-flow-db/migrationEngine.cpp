#include "migrationEngine.hpp"


MigrationEngine::MigrationEngine() {}
MigrationEngine::~MigrationEngine() {}


void MigrationEngine::addMigration(const int& version, std::function<void(std::shared_ptr<Storage>)> task) {
    m_tasks[version] = task;
}

const int MigrationEngine::currentVersion() const {
    if(m_tasks.empty())
        return 0;
    
    return (m_tasks.rbegin())->first;
}


void MigrationEngine::execute(std::shared_ptr<Storage> storage, std::vector<int> versions) {
    if (versions.size()) {
        for (auto version: versions) {
            auto taskIt = m_tasks.find(version);
            if (taskIt != m_tasks.end()) {
                taskIt->second(storage);
            }
        }
    } else {
        for(auto task : m_tasks) {
            task.second(storage);
        }
    }
    
}

std::vector<int> MigrationEngine::shouldRun(std::shared_ptr<Storage> storage) {
    auto m = MigrationTable(storage);
    std::vector<int> versions;

    m.fetch();
    for(auto mig: m) {
        if( m_tasks.find(mig->version.get()) == m_tasks.end())
            versions.push_back(mig->version.get());
    }
    return versions;
}