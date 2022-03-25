#include "LoggingObserver.h"
#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../GameEngine/GameEngine.h"
#include "../CommandProcessing//CommandProcessing.h"

    int main() {

        /****************************** CREATING Game, CommandProcessor, OrdersList, etc. *******************************/

        LogObserver("gamelog.txt");

        /**** Setting up the Game Engine ****/
        MapLoader* loader;
        Map* mainmap = new Map(loader->load("../Orders/canada.map"));

        // Create Players List
        vector<Player*> player_list;
        Player* player1 = new Player(); player1->setReinforcementPool(10); player1->setName("Audrey");
        Player* player2 = new Player(); player2->setReinforcementPool(12); player2->setName("MJ");
        player_list.push_back(player1); player_list.push_back(player2);

        // Create & Set up Game Engine
        GameEngine* mainGE = new GameEngine();
        mainGE->setMap(*mainmap);
        mainGE->setplayer_list(player_list);
        mainGE->setDeck(*new Deck(20));
        Order::game = mainGE;

        // Assign Territories to Players
        int playerIndex = 0;
        for (Territory *i : mainmap->getTerritories()) {
            Player *tempPlayer = player_list.at(playerIndex);
            i->setOwner(tempPlayer);
            tempPlayer->assignTerritory(i);

            playerIndex++;
            if (playerIndex >= player_list.size()) {
                playerIndex = 0;
            }
        }
        Territory* Yukon_Territory = Order::game->getMap()->getTerritories().at(30); Yukon_Territory->setArmies(4);
        Territory* Ontario_South = Order::game->getMap()->getTerritories().at(8); Ontario_South->setArmies(0);
        Territory* Ontario_North = Order::game->getMap()->getTerritories().at(10); Ontario_North->setArmies(0);
        Territory* Quebec_Central = Order::game->getMap()->getTerritories().at(6); Quebec_Central->setArmies(4);
        Territory* Manitoba_South = Order::game->getMap()->getTerritories().at(11); Manitoba_South->setArmies(4);
        Territory* Ontario_West = Order::game->getMap()->getTerritories().at(9); Ontario_West->setArmies(4);
        Territory* Quebec_South = Order::game->getMap()->getTerritories().at(7); Quebec_South->setArmies(0);
        Territory* Quebec_North = Order::game->getMap()->getTerritories().at(5); Quebec_North->setArmies(0);

        /**** Commmand & CommandProcessor ****/
        Command *command1 = new Command();
        CommandProcessor *commandProcessor1 = new CommandProcessor();

        /**** OrderList & Order ****/


        /****************************** CLASSES INHERITING FROM SUBJECT & ILOGGABLE *******************************/

        bool subjectGameEngine = is_base_of<Subject, GameEngine>::value;
        bool subjectCommand = is_base_of<Subject, Command>::value;
        bool subjectCommandProcessor = is_base_of<Subject, CommandProcessor>::value;
        bool subjectOrdersList = is_base_of<Subject, OrdersList>::value;
        bool subjectOrder = is_base_of<Subject, Order>::value;

        cout << "\n--------- Inheritance of Class Subject\n" << endl;
        if (subjectGameEngine) { cout << "GameEngine inherits from Subject" << endl;}
        if (subjectCommand) { cout << "Command inherits from Subject"  << endl;}
        if (subjectCommandProcessor) { cout << "CommandProcessor inherits from Subject"  << endl;}
        if (subjectOrdersList) { cout << "OrdersList inherits from Subject" << endl;}
        if (subjectOrder) { cout << "Order inherits from Subject" << endl;}

        bool iloggableGameEngine = is_base_of<Iloggable, GameEngine>::value;
        bool iloggableCommand = is_base_of<Iloggable, Command>::value;
        bool iloggableCommandProcessor = is_base_of<Iloggable, CommandProcessor>::value;
        bool iloggableOrdersList = is_base_of<Iloggable, OrdersList>::value;
        bool iloggableOrder = is_base_of<Iloggable, Order>::value;

        cout << "\n--------- Inheritance of Class Iloggable\n" << endl;
        if (iloggableGameEngine) { cout << "GameEngine inherits from Iloggable\n";}
        if (iloggableCommand) { cout << "Command inherits from Iloggable\n";}
        if (iloggableCommandProcessor) { cout << "CommandProcessor inherits from Iloggable\n";}
        if (iloggableOrdersList) { cout << "OrdersList inherits from Iloggable\n";}
        if (iloggableOrder) { cout << "Order inherits from Iloggable\n";}

        /****************************** Methods using the Observer Pattern *******************************/

//        cout << "\n-------------------- CommandProcessor::saveCommand() --------------------" << endl;
//        cout << "\n--------- Read Command from Console" << endl;
//        cout << "\n--------- Read Commmand from file" << endl;
//
//        cout << "\n-------------------- Command::SaveEffect --------------------" << endl;
//
//        cout << "\n-------------------- GameEngine::transition() --------------------" << endl;
//        cout << "\n--------- Changing State to loadmap" << endl;
//        cout << "\n--------- Changing State to validatemap" << endl;

        cout << "\n-------------------- OrderList::addOrder() --------------------" << endl;
        Deploy* deploy1 = new Deploy(player1, Ontario_South);
        Deploy* deploy2 = new Deploy(player2, Quebec_North);
        Deploy* deploy3 = new Deploy(player1, Ontario_West);

        player1->getOrder()->addOrder(deploy1);
        player1->getOrder()->addOrder(deploy2);
        player1->getOrder()->addOrder(deploy3);

        cout << "\n-------------------- Order::execute() --------------------" << endl;

        cout << "\n--------- Player 1 Deploy" << endl;
        cout << "Order: " << *deploy1 << endl;
        deploy1->validate();
        deploy1->execute();

        cout << "\n--------- Player 2 Deploy" << endl;
        cout << "Order: " << *deploy2 << endl;
        deploy2->validate();
        deploy2->execute();

        cout << "\n--------- Player 1 Deploy (Target belongs to another player)" << endl;
        cout << "Order: " << *deploy3 << endl;
        deploy3->validate();
        deploy3->execute();

        return 0;

    }