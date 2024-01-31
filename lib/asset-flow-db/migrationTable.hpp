#pragma once

#include <spdlog/spdlog.h>

#include "table.hpp"


class MigrationTable : public Table {
public:
    MigrationTable(std::shared_ptr<Storage> db) : Table(db) {};

    struct Data {
        Cell<int> id;
        Cell<int> version;
        Data(const int& v) {
            id = Cell(0, "id", "int");
            version = Cell(v, "version", "int");
        };
        Data(const Data& other) {
            id = other.id;
            version = other.version;
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
    const char* m_tableName = "migration";
};