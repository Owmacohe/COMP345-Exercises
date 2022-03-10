cmake_minimum_required(VERSION 3.21)
project(COMP345_Assignment)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(COMP345-Exercises
        Cards/Cards.cpp
        Cards/Cards.h
        CommandProcessing/CommandProcessing.h
        CommandProcessing/CommandProcessing.cpp
        GameEngine/GameEngine.cpp
        GameEngine/GameEngine.h
        LoggingObserver/LoggingObserver.cpp
        LoggingObserver/LoggingObserver.h
        Map/Map.cpp
        Map/Map.h
        Orders/Orders.cpp
        Orders/Orders.h
        Orders/OrdersDriver.cpp
        Player/Player.cpp
        Player/Player.h
        )
