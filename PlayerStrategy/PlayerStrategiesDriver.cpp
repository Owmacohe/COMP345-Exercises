#include "PlayerStrategies.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../GameEngine/GameEngine.h"
#include "../Cards/Cards.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Create Map Loader
    MapLoader* loader;
    Map *mainmap = loader->load("../Orders/canada.map");

    // Create Players List
    vector<Player*> player_list;
    Player* player1 = new Player();
    HumanPlayerStrategy* humanstrat = new HumanPlayerStrategy(player1);
    player1->setStrategy(humanstrat); player1->setReinforcementPool(12); player1->setName("Audrey");

    Player* player2 = new Player();
    NeutralPlayerStrategy* neutralstrat = new NeutralPlayerStrategy(player2);
    player2->setStrategy(neutralstrat); player2->setReinforcementPool(10); player2->setName("MJ");

    Player* player3 = new Player();
    BenevolentPlayerStrategy* benevolentstrat = new BenevolentPlayerStrategy(player3);
    player3->setStrategy(benevolentstrat); player3->setReinforcementPool(8); player3->setName("Gabbi");

    Player* player4 = new Player();
    AggressivePlayerStrategy* aggressivestrat = new AggressivePlayerStrategy(player2);
    player4->setStrategy(aggressivestrat); player4->setReinforcementPool(6); player4->setName("Owen");

    Player* player5 = new Player();
    CheaterPlayerStrategy* cheaterstrat = new CheaterPlayerStrategy(player5);
    player5->setStrategy(cheaterstrat); player5->setReinforcementPool(4); player5->setName("Joe");

    player_list.push_back(player1); player_list.push_back(player2); player_list.push_back(player3); player_list.push_back(player4); player_list.push_back(player5);

    // Create & Set up Game Engine
    GameEngine* mainGE = new GameEngine();
    mainGE->setMap(mainmap);
    mainGE->setplayer_list(player_list);
    mainGE->setNumberOfPlayers(3);
    PlayerStrategies::game = mainGE;
    Order::game = mainGE;

    // Set up player order
    vector<int> tempOrder;
    for (int j = 0; j < mainGE->getplayer_list().size(); j++) {
        int randOrder = rand() % mainGE->getplayer_list().size();

        while (doesContain(tempOrder, randOrder)) {
            randOrder = rand() % mainGE->getplayer_list().size();
        }
        tempOrder.push_back(randOrder);
    }
    mainGE->setPlayerOrder(tempOrder);

    // Assign Territories to Players
    int playerIndex = 0;
    for (Territory *i : mainmap->getTerritories()) {
        Player *tempPlayer = mainGE->getplayer_list().at(playerIndex);
        i->setOwner(tempPlayer);
        tempPlayer->assignTerritory(i);

        playerIndex++;
        if (playerIndex >= mainGE->getplayer_list().size()) {
            playerIndex = 0;
        }
    }

    // Display Player list of Territories
    cout << endl;
    for (int i = 0; i < mainGE->getplayer_list().size(); i++){
        cout << mainGE->getplayer_list().at(i)->getName() << "'s territories: ";
        for(auto teri : mainGE->getplayer_list().at(i)->getTerritoryList()){
            cout << teri->getName() << " | ";
        }
        cout << endl;
    }
    cout << endl;

    // Give Player Cards
    for (Player* p : mainGE->getplayer_list()) {
        p->getHand()->drawCard(*(mainGE->getDeck()));
        p->getHand()->drawCard(*(mainGE->getDeck()));
        p->getHand()->drawCard(*(mainGE->getDeck()));
    }

    /****************************** Human *******************************/
//    player1->issueOrder("advance"); // attack - New_Brunswick -> Prince_Edward_Island
                                                // to test neutral to aggressive switch
//                                              // neutral attack : Ontario-North, Ontario-South
//                                              // neutral attack : Nunavut-Continental, NU-Victoria_Island-East
//    cout << *player1->toAttack().at(0) << endl; // attack - Quebec-North -> Quebec-Central
//    player1->issueOrder("deploy"); // move - Quebec-North -> New_Brunswick
//    cout << *player1->toDefend().at(0) << endl; //Nunavut-Continental

    /****************************** Aggressive *******************************/
//    player2->issueOrder("deploy");
//    player2->issueOrder("deploy");
//    player2->issueOrder("advance");
    player2->getHand()->drawCard(*PlayerStrategies::game->getDeck());
    /****************************** Benevolent *******************************/
    cout<< "****************************** Benevolent *******************************"<<endl;
    cout<< " before deploy"<<endl;


/*Setting the number of armies for each territory from 0-n to make sure that there is a territory having 0 armies which will be the weakest terrirtory in this case
 * and tests if the strategy will issue a deploy order to deploy armies to this territory*/

        for(int i = 0; i<player3->getTerritoryList().size();i++){
                player3->getTerritoryList().at(i)->setArmies(i);
            }

        for (Territory *t : player3->getTerritoryList()){
                cout<< t->getName()<< " " << t->getArmies()<<endl;
            }

        player3->setReinforcementPool(1);

        player3->issueOrder("deploy");
        int j = 0;
        for(Order * o : player3->getOrder()->getOrderList()){

                cout<< o->getDescription()<<endl;
                o->validate();
                o->execute();
                player3->getOrder()->remove(j);
                j++;
            }

        cout<< "after deploy"<<endl;

        for (Territory *t : player3->getTerritoryList()){
                cout<< t->getName()<< " " << t->getArmies()<<endl;
            }

            /*test for advance--> making sure that one of the territories has a weaker one connected to it to test the strategy for the advance order */
    cout<<"adding new territories which are connected to one of the players territories just to show that the advance will move armies to the weakest territory"<<endl;
            vector<Territory*> conncetedTerrs = vector<Territory*>();
            conncetedTerrs = mainmap->getConnectedTerritories(player3->getTerritoryList().at(0)->getName());
            for (int i =0 ; i< conncetedTerrs.size() ; i++){
                conncetedTerrs.at(i)->setOwner(player3);
                conncetedTerrs.at(i)->setArmies(i);
                player3->assignTerritory(conncetedTerrs.at(i));

            }
        cout<< "before advance"<<endl;

        for (Territory *t : player3->getTerritoryList()){
            cout<< t->getName()<< " " << t->getArmies()<<endl;
        }
            player3->issueOrder("advance");
        j=0;
        for(Order * o : player3->getOrder()->getOrderList()){
            cout<< o->getDescription()<<endl;
            o->validate();
            o->execute();
            player3->getOrder()->remove(j);
            j++;
        }

        cout<< "after advance"<<endl;

        for (Territory *t : player3->getTerritoryList()){
            cout<< t->getName()<< " " << t->getArmies()<<endl;
        }

//TODO: there is an issue with draw card but testing the cards works with the cards the player has already in hand try to run it multiple times it will only get the 2 types of cards
            /* test for cards --> drawing 10 random cards to show that any card issued will be only of type airlift or blockade*/
//            for(int i = 0 ; i<10 ; i++){
//                player3->getHand()->drawCard(*PlayerStrategies::game->getDeck());
//
//            }
cout<<"cards in hand"<<endl;
            for(Card * c : player3->getHand()->hand){
                cout<<c->getType()<<endl;
            }
            player3->issueOrder("card");

            //

    if (player3->getOrder()->getOrderList().size()>0)  cout<<"card played :" <<player3->getOrder()->getOrderList().at(0)->getDescription()<<endl;
    else  cout<<"the player doesn't have blockade or airlift so he's not allowed to play any other type of card"<<endl;



    /****************************** Neutral *******************************/
    // show that neutral can turn into aggressive, test using the human
    // Testing Neutral -> Aggressive
    //    cout << player4->getPlayerStrategy()->getType() << endl;
    //
    //    mainGE->issueOrdersPhase(); // testing without benevolent or cheater use Quebec-Central and Quebec-North
    //
    //    cout << player4->getPlayerStrategy()->getType() << endl;
    /****************************** Cheater *******************************/

    cout<<"/****************************** Cheater *******************************/"<<endl;

    /* test for deploy*/
    cout<< " before deploy"<<endl;

    for(int i = 0; i<player5->getTerritoryList().size();i++){
        player5->getTerritoryList().at(i)->setArmies(i);
    }
    for (Territory *t : player5->getTerritoryList()){
        cout<< t->getName()<< " " << t->getArmies()<<endl;
    }
    player5->setReinforcementPool(1);

    player5->issueOrder("deploy");

    int k = 0;
    for(Order * o : player5->getOrder()->getOrderList()){
        if (o->getDescription() == "deploy") {
            cout << o->getDescription() << endl;
            o->validate();
            o->execute();
            player5->getOrder()->remove(k);
            k++;
        }
    }
    cout<< "after deploy"<<endl;
    for (Territory *t : player5->getTerritoryList()){
        cout<< t->getName()<< " " << t->getArmies()<<endl;
    }
/* test for advance */
    cout<<"*********************cheater name is "<< player5->getName() << "*****************************"<<endl;
    conncetedTerrs.clear();

    for(Territory * t : player5->getTerritoryList()){
       conncetedTerrs = mainmap->getConnectedTerritories(t->getName()) ;
        for (Territory *ter : conncetedTerrs) {
            cout<< ter->getName() << "    "<< ter->getOwnerName()<< endl;

        }
    }

    player5->issueOrder("advance");

     k = 0;
    for(Order * o : player5->getOrder()->getOrderList()){
        if (o->getDescription() == "advance") {
            cout << o->getDescription() << endl;
            o->validate();
            o->execute();
            player5->getOrder()->remove(k);
            k++;
        }
    }
    for(Territory * terri : player5->getTerritoryList()){
        cout<< terri->getName() << "    "<< terri->getOwnerName()<< endl;
    }

/* test for cards*/
    player5->issueOrder("card");

    return 0;
}