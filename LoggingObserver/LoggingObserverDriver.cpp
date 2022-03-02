#include "LoggingObserver.h"
#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../GameEngine/GameEngine.h"

#include "../Cards/Cards.cpp"
#include "../Orders/Orders.cpp"
#include "../Map/Map.cpp"
#include "../Player/Player.cpp"
#include "../GameEngine/GameEngine.cpp"

int LoggingObserverMain() {

//            (1) Show that classes inherit from subject and Iloggable
//            (2) SaveCommand, Execute, saveEffect, addOrder, Transition methods use Notify(Subject)
//            (3) gamelog.txt file is correctly written
//            (4) addOrder to Orderlist from a player actually outputs on file
//            (5) When an Order is executed, output to file
//            (6) GameEngine changes state, output to file

    return 0;
}