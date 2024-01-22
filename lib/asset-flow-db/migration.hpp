#pragma once

#include <vector>
#include <functional>

class Storage;

class MigrationEngine {
public:
    MigrationEngine(const int& version, std::vector<std::function<void(Storage*)>> tasks);
    ~MigrationEngine();

    void execute(Storage* storage);
    bool shouldRun(Storage* storage);
private:
    int m_version;
    std::vector<std::function<void(Storage*)>> m_tasks;
};