#pragma once

#include <ctime>
#include <string>
#include <filesystem>
#include <sstream>

#include <spdlog/spdlog.h>

#include "table.hpp"


class AssetTable : public Table {
public:
    AssetTable(std::shared_ptr<Storage> db) : Table(db) {};

    struct Data {
        Cell<int> id;
        Cell<std::string> name;
        Cell<std::string> description;
        Cell<std::filesystem::path> path;
        Cell<std::string> extension;
        Cell<std::string> dateCreation;
        Cell<std::string> dateModified;

        Data() {
            id = Cell(0, "id", "int");
            name = Cell(std::string(), "name", "TEXT");
            description = Cell(std::string(), "description", "TEXT");
            path = Cell(std::filesystem::path(), "path", "TEXT");
            extension = Cell(std::string(), "extension", "TEXT");
            dateCreation = Cell(std::string(), "dateCreation", "TEXT");
            dateModified = Cell(std::string(), "dateModified", "TEXT");
        };
        Data(const Data& other) {
            id = other.id;
            name = other.name;
            description = other.description;
            path = other.path;
            extension = other.extension;
            dateCreation = other.dateCreation;
            dateModified = other.dateModified;
        }
    };
    typedef std::vector<std::shared_ptr<Data>> TableData;
    typedef TableData::iterator iterator;
    typedef TableData::const_iterator constIterator;

    virtual void fetch();
    virtual void fetch(const Query& query);
    virtual void create();
    virtual void update();
    virtual void insert(const Data& data);
    virtual void remove(const Data& data);

    iterator begin() {return m_data.begin();};
    iterator end() {return m_data.end();};
    virtual std::size_t size() {return m_data.size();};

    std::shared_ptr<Data> operator[](const int& index);
private:
    TableData m_data;
    const char* m_tableName = "asset";
};