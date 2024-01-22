#include "entities.hpp"
#include <sstream>

std::string Migration::getFullSchema() {
    std::stringstream ss;
    ss << "Migration( " << 
        id.name() << " INTEGER PRIMARY KEY AUTOINCREMENT, " <<
        version.name() << " INT NOT NULL );";
    return ss.str();
}

std::string Migration::getFieldList() {
    return "Migration(" + id.name() + ", " + version.name() + ")"; 
}