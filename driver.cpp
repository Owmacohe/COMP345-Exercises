#include <iostream>
using namespace std;

#include "Cards/Cards.h"
#include "Map/Map.h"
#include "Orders/Orders.h"
#include "Player/Player.h"

#include "Map/MapDriver.cpp"
#include "GameEngine/GameEngineDriver.cpp"
#include "Cards/CardsDriver.cpp"
#include "Player/PlayerDriver.cpp"
#include "Orders/OrdersDriver.cpp"

int main() {
    mapMain();
    gameEngineMain();
    cardsMain();
    playerMain();
    ordersMain();

    return 0;
}