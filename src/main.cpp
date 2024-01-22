
#include <filesystem>
#include "asset-flow-db/storage.hpp"




int main() {
    std::filesystem::path path("./database.db");
    auto strg = Storage(path);
    
    return 0;
}