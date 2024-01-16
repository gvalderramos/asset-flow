#pragma once

#include "asset-flow-db/field.hpp"


struct Migration {
    Field<int> version;
}