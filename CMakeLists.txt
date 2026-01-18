cmake_minimum_required(VERSION 3.30)
project(Dschoutezo_ProgettoTransazioni)

set(CMAKE_CXX_STANDARD 20)

add_library(coreProject
        Account.cpp
        Account.h
        Transaction.cpp
        Transaction.h
        Date.cpp
        Date.h
)

target_include_directories(coreProject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(Dschoutezo_ProgettoTransazioni main.cpp )

target_link_libraries(Dschoutezo_ProgettoTransazioni PRIVATE coreProject)

enable_testing()
add_subdirectory(test)