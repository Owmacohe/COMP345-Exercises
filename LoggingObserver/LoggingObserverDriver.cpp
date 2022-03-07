#include "LoggingObserver.h"
#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../GameEngine/GameEngine.h"
#include "../CommandProcessing//CommandProcessing.h"

//int LoggingObservermain() {
//    int main() {
//
//        LogObserver("gamelog.txt");
//        GameEngine *game = new GameEngine();
//        Command *command1 = new Command();
//        CommandProcessor *commandProcessor1 = new CommandProcessor();
//        OrdersList *orderList1 = new OrdersList();
//        Order *order1 = new Order();
//
//        //            (1) Show that classes inherit from subject and Iloggable
//        Subject* subjectGameEngine = dynamic_cast<Subject*> (game);
//        Subject* subjectCommand = dynamic_cast<Subject*> (command1);
//        Subject* subjectCommandProcessor = dynamic_cast<Subject*> (commandProcessor1);
//        Subject* subjectOrdersList = dynamic_cast<Subject*> (orderList1);
//        Subject* subjectOrder = dynamic_cast<Subject*> (order1);
//
//        if (subjectGameEngine != NULL) { cout << "GameEngine inherits from Subject\n";}
//        if (subjectCommand!= NULL) { cout << "Command inherits from Subject\n";}
//        if (subjectCommandProcessor != NULL) { cout << "CommandProcessor inherits from Subject\n";}
//        if (subjectOrdersList != NULL) { cout << "OrdersList inherits from Subject\n";}
//        if (subjectOrder != NULL) { cout << "Order inherits from Subject\n";}
//
//        Iloggable* iloggableGameEngine = dynamic_cast<Iloggable*> (game);
//        Iloggable* iloggableCommand = dynamic_cast<Iloggable*> (command1);
//        Iloggable* iloggableCommandProcessor = dynamic_cast<Iloggable*> (commandProcessor1);
//        Iloggable* iloggableOrdersList = dynamic_cast<Iloggable*> (orderList1);
//        Iloggable* iloggableOrder = dynamic_cast<Iloggable*> (order1);
//
//        if (iloggableGameEngine != NULL) { cout << "GameEngine inherits from Iloggable\n";}
//        if (iloggableCommand != NULL) { cout << "Command inherits from Iloggable\n";}
//        if (iloggableCommandProcessor != NULL) { cout << "CommandProcessor inherits from Iloggable\n";}
//        if (iloggableOrdersList != NULL) { cout << "OrdersList inherits from Iloggable\n";}
//        if (iloggableOrder != NULL) { cout << "Order inherits from Iloggable\n";}
//
//        //            (2) SaveCommand
//        //            Execute
//        //            saveEffect
//        //            addOrder
//        //            Transition methods use Notify(Subject)
//
//        game->gameStartupTransitions("loadmap");
//
//        //game->gamePlayTransitions("issueOrder", player1);
//        //game->gameEndTransitions();
//
//        command1->saveEffect("validatemap");
//
//        commandProcessor1->saveCommand(*command1);
//
//
//
//        //            (3) gamelog.txt file is correctly written when it receives commands from console
//
//        //            (4) addOrder to Orderlist from a player actually outputs on file
//        Player *player1 = new Player();
//        player1->setName("testPlayer");
//        player1->issueOrder(5);
//
//        //            (5) When an Order is executed, output to file
//        order1->execute();
//
//        //            (6) GameEngine changes state, output to file
//
//
//
//        return 0;

    }