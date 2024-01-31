#include "assetTable.hpp"


void AssetTable::fetch() {
    fetch(Query(Query::QueryMethod::Select, m_tableName));
}
void AssetTable::fetch(const Query& query){
    m_db->interact(
        query, 
        [&](sqlite3_stmt* stmt){
            auto step = sqlite3_step(stmt);

            while(step == SQLITE_ROW) {
                auto numCols = sqlite3_column_count(stmt);
                spdlog::debug("Found {:02d} columns in the asset table", numCols);
                if(numCols <= 0) {
                    break;
                }

                auto data = std::shared_ptr<Data>();
                data->id.set(sqlite3_column_int(stmt, 0));
                data->name.set(
                    std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)))
                );
                data->description.set(
                    std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)))
                );
                data->path.set(
                    std::filesystem::path(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)))
                );
                data->extension.set(
                    std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)))
                );
                data->dateCreation.set(
                    std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)))
                );
                data->dateModified.set(
                    std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)))
                );

                m_data.push_back(data);
                step = sqlite3_step(stmt);
            }
        }
    );
}
void AssetTable::create(){
    const std::string squema = std::string(m_tableName) + "("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "description TEXT, "
        "path TEXT NOT NULL, "
        "extension TEXT NOT NULL, "
        "dateCreation TEXT NOT NULL, "
        "dateModified TEXT NOT NULL);";
    m_db->interact(
        Query(Query::QueryMethod::Create, squema)
    );
}

void AssetTable::update(){
    for(auto data: m_data) {
        m_db->interact(
            Query(Query::QueryMethod::Update, m_tableName)
                .set("name", data->name.get())
                .set("description", data->description.get())
                .set("path", data->path.get().string())
                .set("extension", data->extension.get())
                .set("dateCreation", data->dateCreation.get())
                .set("dateModifed", data->dateModified.get())
                .where("id").isEqual(std::to_string(data->id.get()))
        );
    }
}

void AssetTable::insert(const AssetTable::Data& data){
    std::stringstream fields, values;
    fields << "name, description, path, extension, dateCreation, dateModified";
    values << data.name.get() << ", "
           << data.description.get() << ", "
           << data.path.get() << ", "
           << data.extension.get() << ", "
           << data.dateCreation.get() << ", "
           << data.dateModified.get();
    m_db->interact(
        Query(Query::QueryMethod::Insert, m_tableName, fields.str())
            .values(values.str())
    );
}

void AssetTable::remove(const AssetTable::Data& data){
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

std::shared_ptr<AssetTable::Data> AssetTable::operator[](const int& index) {
    if (index >= 0 && index <= size())
        return m_data[index];

    spdlog::error("Index out of range");
    return nullptr;
}