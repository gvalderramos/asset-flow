#pragma once

#include <set>
#include <vector>
#include <string>
#include <sstream>


class Query {
public:
    enum class QueryMethod {
        Select = 0,
        Insert,
        Update,
        Delete,
        Create,
    };
    Query(const QueryMethod& method, const std::string& tableName, const std::string& fields="*") : m_tableName(tableName) {
        switch (method)
        {
        case QueryMethod::Select:
            m_sqlQuery << "SELECT " << fields << " FROM " << m_tableName << " ";
            break;
        case QueryMethod::Insert:
            m_sqlQuery << "INSERT INTO " << m_tableName << " ";
            if(fields != "*") {
                m_sqlQuery << " (" << fields << ") ";
            }
            break;
        case QueryMethod::Update:
            m_sqlQuery << "UPDATE " << m_tableName << " ";
            break;
        case QueryMethod::Delete:
            m_sqlQuery << "DELETE FROM " << m_tableName << " ";
            break;
        case QueryMethod::Create:
            m_sqlQuery << "CREATE TABLE IF NOT EXISTS " << m_tableName << " ";
            break;
        default:
            break;
        }
        
    };
    ~Query() {};

    Query& where(const std::string& fieldName) {
        m_sqlQuery << "WHERE " << fieldName << " ";
        return *this;
    };
    Query& isEqual(const std::string& value) {
        m_sqlQuery << " = " << value << " ";
        return *this;
    };
    Query& also(const std::string& result){
        m_sqlQuery << " AND ";
        return *this;
    };
    Query& either(const std::string& result) {
        m_sqlQuery << " OR ";
        return *this;
    };
    Query& in(const std::string& result){
        m_sqlQuery << " IN ";
        return *this;
    };
    Query& values(const std::string& values) {
        m_sqlQuery << "VALUES(" << values << ")";
        return * this;
    }
    Query& set(const std::string& field, const std::string& value) {
        m_sqlQuery << " SET " << field << " = " << value << " ";
        return *this;
    }

    std::string str() const {
        // m_sqlQuery << "; ";
        // auto res = m_sqlQuery.str();
        auto sqlQuery = m_sqlQuery.str();
        sqlQuery += "; ";

        // m_sqlQuery.clear();
        return sqlQuery;
    }

    const inline std::string tableName() const {return m_tableName; };

private:
    std::string m_tableName;
    std::stringstream m_sqlQuery;
};