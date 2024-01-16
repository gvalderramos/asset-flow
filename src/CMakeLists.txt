
file(GLOB_RECURSE ASSET_FLOW_MANAGER_SRC *.cpp *.hpp)

add_executable(asset-flow-manager ${ASSET_FLOW_MANAGER_SRC})

install(TARGETS asset-flow-manager DESTINATION bin)
target_link_libraries(asset-flow-manager PUBLIC asset-flow-db)
