#pragma once

#include "asset-flow-db/field.hpp"

struct Entity {
    Field<int> id;
    
    virtual std::string getFullSchema() = 0;
    virtual std::string getFieldList() = 0;
};

struct Migration : public Entity {
    Field<int> version;

    virtual std::string getFullSchema();
    virtual std::string getFieldList();
};