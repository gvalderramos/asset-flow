#include "storage.hpp"


Storage::Storage(const std::filesystem::path& path)
    : m_location(path)
{
    if (!std::filesystem::exists(m_location.parent_path())) {
        std::filesystem::create_directories(m_location.parent_path());
    }
    open();
    checkMigrations();
}

Storage::~Storage() {
    close();
}

void Storage::open() {
    int exit = 0;
    exit = sqlite3_open(m_location.string().c_str(), &m_db);

    if (exit != SQLITE_OK) {
        std::cerr << "Error while opening the database! ERROR: " << exit << std::endl;
    }
}

void Storage::close() {
    sqlite3_close(m_db);
}

void Storage::checkMigrations() {

}