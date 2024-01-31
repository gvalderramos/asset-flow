#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "query.hpp"
#include "storage.hpp"


class Table {
public:
    Table() = delete;
    Table(Table& table) = delete;
    Table(const Table& table) = delete;
    explicit Table(std::shared_ptr<Storage> db) : m_db(db) {};
    ~Table() {};

    template <typename T>
    class Cell
    {
    private:
        T m_value;
        std::string m_name;
        std::string m_type;
        bool m_valueChanged;
    
    public:
        Cell() {};
        Cell(const Cell& other) {
            m_value = other.m_value;
            m_name = other.m_name;
            m_type = other.m_type;
            m_valueChanged = other.m_valueChanged;
        }
        Cell(const T& value, const std::string& name, const std::string& type) 
            : m_value(value), m_name(name), m_type(type), m_valueChanged(false) 
        {        
        };

        inline const T get() const {return m_value; };
        inline const void set(const T& value) {m_value = value; m_valueChanged = true;};
        inline const bool hasChanged() const {return m_valueChanged;};
        inline const void hasUpdated() {m_valueChanged = false;};
    };

    struct Data;
    typedef std::vector<std::shared_ptr<Data>> TableData;
    typedef TableData::iterator iterator;
    typedef TableData::const_iterator constIterator;

    virtual void fetch() = 0;
    virtual void fetch(const Query& query) = 0;
    virtual void create() = 0;
    virtual void update() = 0;
    virtual void insert(const Data& data) {};
    virtual void remove(const Data& data) {};
    
    virtual std::size_t size() = 0;
protected:
    std::shared_ptr<Storage> m_db;
};