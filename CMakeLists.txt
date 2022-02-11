cmake_minimum_required(VERSION 3.21)
project(COMP345_Exercises)

set(CMAKE_CXX_STANDARD 14)

add_executable(COMP345_Exercises
        Cards/Cards.h
        Cards/Cards.cpp
#        Cards/CardsDriver.cpp
        Orders/Orders.h
        Orders/Orders.cpp
#        Orders/OrdersDriver.cpp
        driver.cpp
        )
