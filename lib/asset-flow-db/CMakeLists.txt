file (GLOB_RECURSE ASSET_FLOW_DB_SRC *.cpp *.hpp *.inl)

add_library(asset-flow-db ${ASSET_FLOW_DB_SRC})

target_include_directories(asset-flow-db PUBLIC "${PROJECT_SOURCE_DIR}/vendor/sqlite3/include" "${spdlog_SOURCE_DIR}/include")

target_link_libraries(asset-flow-db PRIVATE sqlite3 spdlog::spdlog)
install(TARGETS asset-flow-db DESTINATION lib)
