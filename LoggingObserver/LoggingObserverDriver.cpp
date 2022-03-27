#include "LoggingObserver.h"
#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../GameEngine/GameEngine.h"
#include "../CommandProcessing//CommandProcessing.h"

LogObserver* logger = new LogObserver("gamelog.txt");
LogObserver* Subject::logObs=logger;

    int LogObsmain() {

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


        cout << "\n-------------------- GameEngine::transition() --------------------" << endl;
        logger->outputFile  << "\n-------------------- GameEngine::transition() --------------------" << endl;
        GameEngine *mainGE = new GameEngine;
        mainGE->transition(start); // contains notify()

        //loading a map
        mainGE->transition(mapLoaded); // contains notify()
        MapLoader* loader;
        Map* mainmap = loader->load("../Orders/canada.map");
        mainGE->transition(mapValidated); // contains notify()

        cout << "\n-------------------- CommandProcessor::saveCommand() --------------------" << endl;
        logger->outputFile << "\n-------------------- CommandProcessor::saveCommand() --------------------" << endl;

        CommandProcessor *cp;
        FileCommandProcessorAdapter *fcpa;

        cout << "\n--------- Read command from file" << endl;
        logger->outputFile << "\n--------- Read command from file" << endl;

        string fileName = "../LoggingObserver/commandLogObs.txt";
        ifstream input(fileName);
        fcpa = new FileCommandProcessorAdapter(fileName);
        cp = fcpa;
        cp->setEngine(mainGE);
        mainGE->setProcessor(cp);
        cp->getCommand(); // Getting a single Command, contains SaveCommand()
        Command *command1 = cp->getCommands()[cp->getCommands().size() - 1];

        cout << command1->getEffect() << endl;

        // Splitting the input into words (if it can be split)
        string effect = "";
        string word1 = "";
        string word2 = "";
        bool hasReachedSpace = false;

        for (char i : command1->getCommand()) { // Contains SaveCommand()
            if (!hasReachedSpace) {
                if (i == ' ') {hasReachedSpace = true;}
                else {word1 += i;}
            }
            else {if (i != '<' && i != '>') {word2 += i;}}
        }

        if (word1 == "addplayer") {
            if (mainGE->getplayer_list().size() >= 6) {
                effect = "Unable to add Player (6 players reached)";
                cout << effect << "!" << endl;}
            else {
                if (word2.length() > 0 && word2[0] != ' ' && word2[word2.length() - 1] != ' ') {
                    Player *p = new Player(word2);
                    mainGE->getplayer_list().push_back(p);
                    mainGE->setNumberOfPlayers(mainGE->getNumberOfPlayers()+1);

                    effect = "Added Player: " + p->getName();
                    cout << effect << "!" << endl;
                    mainGE->transition(playersAdded);}
                else { effect = "Unable to add Player";
                        cout << effect << "!" << endl;}
            }
        }

        cout << "\n-------------------- Command::SaveEffect --------------------" << endl;
        logger->outputFile << "\n-------------------- Command::SaveEffect --------------------" << endl;
        command1->saveEffect(effect);
        cout << command1->getEffect() << endl;

/*
        cout << "\n--------- Read Command from Console" << endl;
        logger->outputFile << "\n--------- Read Command from Console" << endl;

        CommandProcessor *cp2 = new CommandProcessor;
        cp = cp2;
        cout << "Please give a command: " << endl;
        cp->getCommand(); // Getting a single Command
        Command *command2 = cp->getCommands()[cp->getCommands().size() - 1];

        // Splitting the input into words (if it can be split)
        for (char i : command1->getCommand()) { // Contains SaveCommand()
            if (!hasReachedSpace) {
                if (i == ' ') {hasReachedSpace = true;}
                else {word1 += i;}
            }
            else {if (i != '<' && i != '>') {word2 += i;}}
        }

        if (word1 == "addplayer") {
            if (mainGE->getplayer_list().size() >= 6) {
                effect = "Unable to add Player (6 players reached)";
                cout << effect << "!" << endl;
            }
            else {
                if (word2.length() > 0 && word2[0] != ' ' && word2[word2.length() - 1] != ' ') {
                    Player *p = new Player(word2);
                    mainGE->getplayer_list().push_back(p);
                    mainGE->setNumberOfPlayers(mainGE->getNumberOfPlayers()+1);

                    effect = "Added Player: " + p->getName();
                    cout << effect << "!" << endl;
                    mainGE->transition(playersAdded);
                }
                else {
                    effect = "Unable to add Player";
                    cout << effect << "!" << endl;
                }
            }
        }

        cout << "\n-------------------- Command::SaveEffect --------------------" << endl;
        logger->outputFile << "\n-------------------- Command::SaveEffect --------------------" << endl;
        command2->saveEffect(effect);

        // Create Players List
        vector<Player*> player_list;
        Player* player1 = new Player();
        player1->setReinforcementPool(10); player1->setName("Audrey");
        Player* player2 = new Player();
        player2->setReinforcementPool(12); player2->setName("MJ");
        player_list.push_back(player1); player_list.push_back(player2);

        // Create & Set up Game Engine
        mainGE->setMap(mainmap);
        mainGE->setplayer_list(player_list);
        mainGE->setDeck(new Deck(20));
        Order::game = mainGE;

        // Assign Territories to Players
        int playerIndex = 0;
        for (Territory *i : mainmap->getTerritories()) {
            Player *tempPlayer = player_list.at(playerIndex);
            i->setOwner(tempPlayer);
            tempPlayer->assignTerritory(i);
            playerIndex++;
            if (playerIndex >= player_list.size()) {playerIndex = 0;}}

        Territory* Yukon_Territory = Order::game->getMap()->getTerritories().at(30); Yukon_Territory->setArmies(4);
        Territory* Ontario_South = Order::game->getMap()->getTerritories().at(8); Ontario_South->setArmies(0);
        Territory* Ontario_North = Order::game->getMap()->getTerritories().at(10); Ontario_North->setArmies(0);
        Territory* Quebec_Central = Order::game->getMap()->getTerritories().at(6); Quebec_Central->setArmies(4);
        Territory* Manitoba_South = Order::game->getMap()->getTerritories().at(11); Manitoba_South->setArmies(4);
        Territory* Ontario_West = Order::game->getMap()->getTerritories().at(9); Ontario_West->setArmies(4);
        Territory* Quebec_South = Order::game->getMap()->getTerritories().at(7); Quebec_South->setArmies(0);
        Territory* Quebec_North = Order::game->getMap()->getTerritories().at(5); Quebec_North->setArmies(0);

        cout << "\n-------------------- CommandProcessor::saveCommand()  --------------------" << endl;

        cout << "\n--------- Read Commmand from file \"commands.txt\"" << endl;
        fileName = "../CommandProcessing/commands.txt";

        cout << "\n--------- Read Command from Console" << endl;

        cout << "\n-------------------- GameEngine::transition() --------------------" << endl;
        cout << "\n--------- Read Commmand from file" << endl;

        cout << "\n--------- Changing State to loadmap" << endl;
        cout << "\n--------- Changing State to validatemap" << endl;

        cout << "\n-------------------- OrderList::addOrder() --------------------" << endl;
        logger->outputFile << "\n-------------------- OrderList::addOrder() --------------------" << endl;
        Deploy* deploy1 = new Deploy(player1, Ontario_South);
        Deploy* deploy2 = new Deploy(player2, Quebec_North);
        Deploy* deploy3 = new Deploy(player1, Ontario_West);

        player1->getOrder()->addOrder(deploy1);
        player1->getOrder()->addOrder(deploy2);
        player1->getOrder()->addOrder(deploy3);
        cout << *player1->getOrder() << endl;

        cout << "\n-------------------- Order::execute() --------------------" << endl;
        logger->outputFile << "\n-------------------- Order::execute() --------------------" << endl;

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
*/
        logger->outputFile << "\n-------------------- Closing the gamelog file --------------------" << endl;
        Order::logObs->outputFile.close();
        return 0;

    }
