cmake_minimum_required(VERSION 3.20)

add_subdirectory(lib/googletest)

add_executable(runAllTest
        TransactionTest.cpp
        AccountTest.cpp
)

target_include_directories(runAllTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(runAllTest PRIVATE gtest_main coreProject)