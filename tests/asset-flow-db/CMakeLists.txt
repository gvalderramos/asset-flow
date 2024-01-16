enable_testing()

add_executable(
  asset-flow-db-test
  field.cc
)
target_link_libraries(
  asset-flow-db-test
  PRIVATE asset-flow-db GTest::gtest_main)
  
target_include_directories(
    asset-flow-db-test
    PRIVATE "${PROJECT_SOURCE_DIR}/lib")

include(GoogleTest)
gtest_discover_tests(asset-flow-db-test)