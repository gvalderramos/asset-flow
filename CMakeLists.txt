cmake_minimum_required(VERSION 3.5)
project(asset-flow VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(DOWNLOAD_EXTRACT_TIMESTAMP ON)

include(FetchContent)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        7c02e204c92545f869e2f04edaab1f19fe8b19fd
)
FetchContent_MakeAvailable(spdlog)
FetchContent_GetProperties(spdlog)


FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(CTest)
# enable_testing()

include_directories(lib)

add_subdirectory(vendor)
add_subdirectory(lib)
add_subdirectory(src)

add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
