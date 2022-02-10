cmake_minimum_required(VERSION 3.21)
project(COMP345_Assignment)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(COMP345-Exercises
        driver.cpp
        Cards/Cards.cpp
        Cards/Cards.h
        Cards/CardsDriver.cpp
        GameEngine/GameEngine.cpp
        GameEngine/GameEngine.h
        GameEngine/GameEngineDriver.cpp
        Map/Map.cpp
        Map/Map.h
        Map/MapDriver.cpp
        Orders/Orders.cpp
        Orders/Orders.h
        Orders/OrdersDriver.cpp
        Player/Player.cpp
        Player/Player.h
        Player/PlayerDriver.cpp
        )
