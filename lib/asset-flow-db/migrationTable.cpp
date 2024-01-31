#include "migrationTable.hpp"


void MigrationTable::fetch() {
    fetch(Query(Query::QueryMethod::Select, m_tableName));
}
void MigrationTable::fetch(const Query& query){
    m_db->interact(
        query, 
        [&](sqlite3_stmt* stmt){
            auto step = sqlite3_step(stmt);

            while(step == SQLITE_ROW) {
                auto numCols = sqlite3_column_count(stmt);
                spdlog::debug("Found {:02d} columns in the migration table", numCols);
                if(numCols <= 0) {
                    break;
                }

                auto data = std::shared_ptr<Data>(new Data(sqlite3_column_int(stmt, 1)));
                data->id.set(sqlite3_column_int(stmt, 0));
                m_data.push_back(data);
                step = sqlite3_step(stmt);
            }
        }
    );
}
void MigrationTable::create(){
    const std::string squema = "migration("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "version INT NOT NULL );";
    m_db->interact(
        Query(Query::QueryMethod::Create, squema)
    );
}

void MigrationTable::update(){
    for(auto data: m_data) {
        m_db->interact(
            Query(Query::QueryMethod::Update, m_tableName)
                .set("version", std::to_string(data->version.get()))
                .where("id").isEqual(std::to_string(data->id.get()))
        );
    }
}

void MigrationTable::insert(const MigrationTable::Data& data){
    m_db->interact(
        Query(Query::QueryMethod::Insert, m_tableName, "version")
            .values(std::to_string(data.version.get()))
    );
}

void MigrationTable::remove(const MigrationTable::Data& data){
    m_db->interact(
        Query(Query::QueryMethod::Delete, m_tableName)
            .where("id").isEqual(std::to_string(data.id.get())),
        [&](sqlite3_stmt* stmt) -> void {
            int index = 0;
            for (auto d: m_data) {
                index ++;
                if (d->id.get() == data.id.get()) {
                    m_data.erase(m_data.begin() + index);
                    break;
                }
            }
        }
    );
}

std::shared_ptr<MigrationTable::Data> MigrationTable::operator[](const int& index) {
    if (index >= 0 && index <= size())
        return m_data[index];

    spdlog::error("Index out of range");
    return nullptr;
}