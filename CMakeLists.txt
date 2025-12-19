cmake_minimum_required(VERSION 3.30)
project(Dschoutezo_ProgettoTransazioni)

set(CMAKE_CXX_STANDARD 20)

add_executable(Dschoutezo_ProgettoTransazioni main.cpp
        Account.cpp
        Account.h
        Transaction.cpp
        Transaction.h
        test/AccountTest.cpp
        test/TransactionTest.cpp)
