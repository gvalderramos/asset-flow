#include "migration.hpp"
#include "entities.hpp"
#include "query.hpp"
#include "storage.inl"


MigrationEngine::MigrationEngine(const int& version, std::vector<std::function<void(Storage*)>> tasks)
    : m_version(version), m_tasks(tasks)
{
}

MigrationEngine::~MigrationEngine() {}

void MigrationEngine::execute(Storage* storage) {
    for(auto task: m_tasks) {
        task(storage);
    }
}

bool MigrationEngine::shouldRun(Storage* storage) {
    auto res = storage->find<Migration>(Query(Query::QueryMethod::Select, "migration").where("id").isEqual(std::to_string(m_version)));
    if(res.size() <= 0) {
        return true;
    }
    return false;
}