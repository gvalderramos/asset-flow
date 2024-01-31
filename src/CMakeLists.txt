
file(GLOB_RECURSE ASSET_FLOW_MANAGER_SRC *.cpp *.hpp)

set(QML_FILES qml/main.qml)
list(APPEND RESOURCES qml.qrc)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Quick)

message(STATUS "QT version: ${QT_VERSION}")

qt_add_resources(RCC_SOURCES ${RESOURCES})
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    # add_library(asset-flow-ui ${ASSET_FLOW_UI_SRC})
    qt_add_executable(asset-flow-manager
        MANUAL_FINALIZATION
        ${RCC_SOURCES}
        ${ASSET_FLOW_MANAGER_SRC}
    )

else()
    add_executable(asset-flow-manager ${ASSET_FLOW_MANAGER_SRC})
endif()

install(TARGETS asset-flow-manager DESTINATION bin)
target_link_libraries(asset-flow-manager PUBLIC asset-flow-db asset-flow-ui Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Quick)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(asset-flow-manager)
endif()
