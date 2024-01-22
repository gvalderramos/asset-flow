#pragma once


#include <map>

#include "asset-flow-db/field.hpp"

enum class Entities {
    Entity = 0,
    Migration,
};

const std::map<std::string, Entities> ENTITIES = {
    {"entity", Entities::Entity},
    {"migration", Entities::Migration},
};

struct Entity {
    Field<int> id;
    
    Entity() : id(Field<int>("id")) {};
    virtual std::string getFullSchema() = 0;
    virtual std::string getFieldList() = 0;
};

struct Migration : public Entity {
    Field<int> version;

    Migration() : version(Field<int>("version")) {};
    virtual std::string getFullSchema();
    virtual std::string getFieldList();
};