#include "GameEngine.h"
#include "../Cards/Cards.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../LoggingObserver/LoggingObserver.h"
#include "../CommandProcessing/CommandProcessing.h"

class OrdersList;
class Player;

// Default constructor
GameEngine::GameEngine() {
    s = new State;
    *s = null;
    NumberOfPlayers = 0;
    NumberOfTerritories = 0;
    deck = new Deck();
    player_list = vector<Player*>();
    Map *map = new Map();
    alliances = set<pair<Player*, Player*>>();

    // Add Neutral Player to Game
    Player* neutralPlayer = new Player();
    neutralPlayer->setName("Neutral");
    player_list.push_back(neutralPlayer);
    // Does not increasing number of players int make something break?

    // Attributes not initialized, CONFIRM WITH TEAM
//    MapLoader *ml;
//    bool phaseEnd;
//    CommandProcessor *processor;

}

// Copy constructor
GameEngine::GameEngine(const GameEngine &gm) {
    s = gm.s;
    NumberOfPlayers = gm.NumberOfPlayers;
    NumberOfTerritories = gm.NumberOfTerritories;
    this->deck = new Deck(*(gm.deck));

    for (Player* p : gm.player_list) {
        this->player_list.push_back(new Player(*p));
    }
    Map *map = new Map(*gm.map);

    alliances = set<pair<Player*, Player*>>();
    for(auto x : gm.alliances) {
        pair<Player*, Player*> pairCopied = make_pair(new Player(*x.first), new Player(*x.second));
        alliances.insert(pairCopied);
    }

    // Attributes not initialized / Destroyed, CONFIRM WITH TEAM
//    MapLoader *ml;
//    bool phaseEnd;
//    CommandProcessor *processor;
}

// Destructor
GameEngine::~GameEngine() {
    delete s;
    s = NULL;

    delete ml;
    ml = NULL;

    delete deck;
    deck = NULL;

    for (Player* p : player_list) {
        delete p;
        p = NULL;
    }

    delete processor;
    processor = NULL;

    delete[] map;
    map = NULL;

    for(auto x : alliances) {
        x.first = NULL;
        x.second = NULL;
    }
    alliances.clear();

    delete playerOrder;
    playerOrder = NULL;
}
// Attributes not initialized / Destroyed, CONFIRM WITH TEAM
//    bool phaseEnd;

// Assignment operator
GameEngine& GameEngine::operator = (const GameEngine& gm) {
    this->s = gm.s;
    NumberOfPlayers = gm.NumberOfPlayers;
    NumberOfTerritories = gm.NumberOfTerritories;
    this->ml = gm.ml;
    phaseEnd = gm.phaseEnd;
    this->deck = gm.deck;

    for (Player* p : gm.player_list) {
        this->player_list.push_back(p);
    }
    
    return *this;
    // Attributes not initialized / Destroyed, CONFIRM WITH TEAM
//    MapLoader *ml;
//    bool phaseEnd;
//    CommandProcessor *processor;
//    alliances = set<pair<Player*, Player*>>();
//    Map *map;
};

// Stream insertion operator
ostream& operator<<(ostream &os, const GameEngine& gm) {
    string p = "";
    for (Player* i : gm.player_list) {
        p += (*i).getName() + " | ";
    }

    return os <<
        "GAME ENGINE: Current state: "<< gm.s <<
        "\n    Players (" << gm.NumberOfPlayers<< "): " <<endl<< p.substr(0, p.length() - 2) <<
        "\n    Number of Territories : (" << gm.NumberOfTerritories << ")" << endl;
}

// Accessors
State GameEngine::getState() { return *s; }
int GameEngine::getNumberOfPlayers() { return NumberOfPlayers; }
bool GameEngine::endOfState() { return phaseEnd; }
vector<Player*> GameEngine::getplayer_list() { return player_list; }
CommandProcessor *GameEngine::getProcessor() { return processor; }
Map *GameEngine::getMap() { return map; }
set<pair<Player*, Player*>> GameEngine::getAlliances() {return alliances;};
bool GameEngine::existingAlliance(Player* p1, Player* p2) {
    for(auto x : alliances) {
        if(x.first == p1) {
            if (x.second == p2)
                return true;
        }
        else if(x.first == p2) {
            if (x.second == p1)
                return true;
        }
    }
    return false;
}
int *GameEngine::getPlayerOrder() { return playerOrder; }

// Mutators
void GameEngine::setState(State s) { this->s = &s; }
void GameEngine::setNumberOfPlayers(int x) { this->NumberOfPlayers = x; }
void GameEngine::setEndOfState(bool b) { this->phaseEnd = b; }
void GameEngine::setProcessor(const CommandProcessor &cp) { *processor = cp; }
void GameEngine::setMap(const Map &m) { *map = m; }
void GameEngine::setAlliances(const set<pair<Player *, Player *>> all) {alliances = all;}
void GameEngine::addAlliances(Player* p1, Player* p2) {alliances.insert(make_pair(p1,p2));}
void GameEngine::resetAlliances() {
    for(auto x : alliances) {
        x.first = NULL;
        x.second = NULL;
    }
    alliances.clear();
}
void GameEngine::setPlayerOrder(int *po) {
    delete[] playerOrder;
    playerOrder = po;
}


// Phases, states, and commands
void GameEngine::startGame() {
    /*
    *s = start;
    cout << "Welcome to Warzone" << endl;
    cout << "Please enter the number of players" << endl;
    cin >> this->NumberOfPlayers;
    cout << "end of start phase" << endl;
    */

   startupPhase();
}

void GameEngine::loadMap() {
    *s = mapLoaded;

    /*
    string mapName;
    cout << "enter map name" << endl;
    cin >> mapName;

    while(mapName != "canada" || mapName != "europe") {
        cout << "incorrect, please re-enter map name" << endl;
        cin >> mapName;
    }
    
    Map m = ml->load(mapName + ".map");
    */

    cout << "Loaded map" << endl;
}

void GameEngine::validateMap() {
    *s = mapValidated;
    cout << "End of map validated phase" << endl;
}

void GameEngine::addPlayer() {
    *s = playersAdded;

    for(int i = 0; i < NumberOfPlayers; i++) {
        string name;
        Player *p = new Player;
        cout << "Please enter the player's name" << endl;
        cin >> name;
        p->setName(name);
        player_list.push_back(p);
    }

    cout << "End of players added phase" << endl;
}

void GameEngine::assignCountries() {
    cout << "End of assign countries command" << endl;
}

void GameEngine::assignReinforcementPhase() {
    *s = assignReinforcement;
    cout << "Assign Reinforcement" << endl;
    // Adding the reset of alliances
    //resetAlliances();
    Player* p = player_list.at(currentPlayer);
    int num = round((p->getNumberOfTerritories())/3);
    if (num < 3) p->addToReinforcePool(3); //minimal number of armies per turn for any player is 3
    else p->addToReinforcePool(num);
    //loop through continenets anad check territories owners
    //need an if to check if player owns a whole continent
    cout << "End of assign Reinforcement" << endl;
}

void GameEngine::issueOrdersPhase() {
    *s = issueOrder;
    for (Player* p : player_list) {
        cout << "Issuing the orders for player " << p->getName() << endl;
        // only issue DEPLOY orders while the players reinforcement pool contains armies
        cout << "Issueing Deploy Orders" << endl;
        while (p->getReinforcePool() != 0) {
            p->issueOrder("deploy");
        }
    }
    // cout << "Reinforcement Pool Empty, All Armies Deployed" << endl;
    // // once reinforcement pool is empty allows player to play advances
    // string console_input;
    // do {
    //     cout << "Would you like to make an advance ? y/n" << endl;
    //     cin >> console_input;
    //     if (console_input == "y" || console_input == "Y") player-> issueOrder("advance");
    //     else break;
    // }
    // while (console_input == "y" || console_input == "Y");
    // // once player is done advancing, player can use cards to issue orders
    // do {
    //     cout << "Would you like to play a card ? y/n" << endl;
    //     cin >> console_input;
    //     if (console_input == "y" || console_input == "Y") player-> issueOrder("card thingy magi");
    //     else break;
    // }
    // while (console_input == "y" || console_input == "Y");
    /*
        do while loop 
        cout << "Would you like to make an advance ? y/n" << endl;
        loop issueOrder("advance");
        • The player issues advance orders to either (1) move armies from one of its own territory to the other in
            order to defend them (using toDefend() to make the decision), and/or (2) move armies from one of its
            territories to a neighboring enemy territory to attack them (using toAttack() to make the decision).
        cout << "Would you like to play a card ? y/n" << endl;
        loop issueOrder("card type");   
        • The player uses one of the cards in their hand to issue an order that corresponds to the card in question.

        while player wants to advance we keep issueing advance orders, once the player is done using advance orders then play cards
        issueOrdersphase should issue the order based on the card played
    */
}

void GameEngine::endIssueOrderPhase(Player *player) {
    *s = executeOrder;
    cout << "End phase issue Orders for player " << player->getName() << endl;
}

void GameEngine::executeOrdersPhase() {
    /*
    //first , adding all deploy orders into a separate list and removing them from the original player's lists
    cout << "Executing Deploy Order" << endl;
    for (int i = 0; i < player_list.size(); i++) {
        for (int j = 0; j < player_list[i]->getOrder()->getOrderList().size(); j++) {
            if (player_list[i]->getOrder()->getOrderList()[j]->description == "Deploy") {
                  player_list[i]->getDeployList()->addOrder(player_list[i]->getOrder()->getOrderList().at(j));
                  player_list.at(i)->getOrder()->remove(j);
            }
        }
    }
    // to execute and remove the deploy orders
    int  deployDoneCount =0;
    while(deployDoneCount < NumberOfPlayers) {
        deployDoneCount =0;
        for (int i = 0; i < player_list.size(); i++) {
            if (!player_list[i]->getDeployList()->getOrderList().empty()) {
                player_list[i]->getDeployList()->getOrderList().at(i)->execute();
                player_list[i]->getOrder()->remove(i);

            } else deployDoneCount++;
        }
    }
    // to execute the rest of the orders on each player's list
    int  playersDone =0;
    while(playersDone < NumberOfPlayers) {
        playersDone =0;
        for (int i = 0; i < player_list.size(); i++) {
            if (!player_list[i]->getOrder()->getOrderList().empty()) {
                player_list[i]->getOrder()->getOrderList().at(i)->execute();
                player_list[i]->getOrder()->remove(i);

            } else {

                playersDone++;
            }
        }
    }
    int lost = 0;
    for (int i = 0 ; i<NumberOfPlayers; i++) {
        if(player_list[i]->getTerritory().size() == 0)
            lost ++ ;
        if (lost == NumberOfPlayers-1) {
            for (int j = 0; j < NumberOfPlayers; j++) {
                if(player_list[j]->getTerritory().size()>0) {
                    winPhase(player_list[j]);
                    break;
                }
                break;
            }
        }else assignReinforcementPhase();
    }
    */
}

void GameEngine::endexecuteOrdersPhase(Player *player) {
    *s = assignReinforcement;
    cout << "End phase execute Order for player " << player->getName() << endl;
}

void GameEngine::winPhase(Player *p) {
    *s = win;
    cout << "victory for player: " << p->getName() << endl;
}

void GameEngine::endPhase() {
    *s = null;
    cout << "Thank you for Playing Warzone" << endl;
}

void GameEngine::playAgain() {
    *s = null;
    cout << "the Game will restart soon" << endl;
}

void GameEngine::gameStartupTransitions(string str) {
    if (str == "loadmap" && (getState() == 1 || getState() == 2)) {
        loadMap();
    }
    else if (str == "validatemap" && getState() == 2) {
        validateMap();
    }
    else if (str == "addplayer" && (getState() ==3 || getState() == 4)) {
       addPlayer();
    }
    else if (str == "assigncountries" && getState() ==4) {
        assignCountries();
        assignReinforcementPhase();
    }
    else {
        cout << "Invalid command!" << endl;
    }

    notify(this); // FROM SUBJECT
}

void GameEngine::gamePlayTransitions(string str, Player *p) {
    if (str == "issueorder" && (getState() == 5 || getState() == 6)) {
        issueOrdersPhase(p);
    }
    else if (str == "endissueorders" && getState() == 6) {
        endIssueOrderPhase(p);
    }
    else if (str == "execorder" && getState() == 7) {
        executeOrdersPhase();
    }
    else if (str == "endexecorders" && getState() == 7) {
        endexecuteOrdersPhase(p);
    }
    else if (str == "win" && getState() == 7) {
        winPhase(p);
    }
    else {
        cout << "Invalid command!" << endl;
    }
    
    notify(this); // FROM SUBJECT
}

void GameEngine::gameEndTransitions(string str) {
    if (str == "end" && getState() == 8) {
        endPhase();
    }
    else if (str == "play" && getState() == 8) {
        playAgain();
    }
    else {
        cout << "Invalid command!" << endl;
    }

    notify(this); // FROM SUBJECT
}

void GameEngine::startupPhase() {
    *s = start;

    cout << "Welcome to Warzone" << endl;

    while (*s < 5) {
        cout << "Enter a command: " << endl;

        processor->getCommand();

        Command temp = processor->getCommands()[processor->commandsLength - 1];

        if (processor->validate(temp)) {
            string word1 = "";
            string word2 = "";
            bool hasReachedSpace = false;

            for (char i : temp.getCommand()) {
                if (!hasReachedSpace) {
                    if (i == ' ') {
                        hasReachedSpace = true;
                    }
                    else {
                        word1 += i;
                    }
                }
                else {
                    if (i != '<' && i != '>') {
                        word2 += i;
                    }
                }
            }

            if (word1 == "loadmap") {
                // use the loadmap <filename> command to select a map from a list of map files as stored in a directory, which results in the map being loaded in the game

                MapLoader loader;
                Map m = Map(loader.load(word2));

                if (m.isGoodMap) {
                    *map = m;
                    cout << "Map loaded!" << endl;
                    *s = mapLoaded;
                }
                else {
                    cout << "Bad map file!" << endl;
                }
            }
            else if (word1 == "validatemap") {
                // use the validatemap command to validate the map (i.e. it is a connected graph, etc – see assignment 1)

                if (map->validate()) {
                    cout << "Map validated!" << endl;
                    *s = mapValidated;
                }
            }
            else if (word1 == "addplayer") { 
                // use the addplayer <playername> command to enter players in the game (2-6 players)

                Player *p;
                p->setName(word2);
                player_list.push_back(p);

                cout << "Player added!" << endl;

                *s = playersAdded;
            }
            else if (word1 == "gamestart") {
               // fairly distribute all the territories to the players

                int playerIndex = 0;

                for (int i = 0; i < map->territoriesLength; i++) {
                    Player *tempPlayer = player_list.at(playerIndex);
                    map->getTerritories()[i].setOwner(tempPlayer);
                    Territory *tempTerr = new Territory(map->getTerritories()[i]);
                    tempPlayer->getTerritory().push_back(tempTerr);

                    playerIndex++;

                    if (playerIndex >= player_list.size()) {
                        playerIndex = 0;
                    }
                }

                // determine randomly the order of play of the players in the game

                int *tempOrder = new int[player_list.size()];

                for (int j = 0; j < player_list.size(); j++) {
                    tempOrder[j] = rand() % (player_list.size() - j) + j;
                }

                setPlayerOrder(tempOrder);

                // give 50 initial armies to the players, which are placed in their respective reinforcement pool

                for (Player* k : player_list) {
                    k->addToReinforcePool(50);
                }

                // let each player draw 2 initial cards from the deck using the deck’s draw() method

                // switch the game to the play phase

                *s = assignReinforcement;
            }
        }
    }

    // ALSO ADD GameEngine Pointer to attribute to Order Class
    //Order::setGameEngine(new );

    notify(this); // FROM SUBJECT
}

void GameEngine::mainGameLoop() {

// You must deliver a driver that demonstrates that (1) a player receives the correct number of armies in the
// reinforcement phase (showing different cases); (2) a player will only issue deploy orders and no other kind of
// orders if they still have armies in their reinforcement pool; (3) a player can issue advance orders to either defend
// or attack, based on the toAttack() and toDefend() lists; (4) a player can play cards to issue orders; (5) a
// player that does not control any territory is removed from the game; (6) the game ends when a single player
// controls all the territories. All of this except the issueOrder() method must be implemented in a single .cpp/.h
// file duo named GameEngine.cpp/GameEngine.h.
}

// Check if a player has won by looping through territtories and checking owner
bool GameEngine::checkForWinner() {
    int count = ;
    for (Player* p : player_list) { 
        string player = p->getName();
        for (int i = 0; i < NumberOfTerritories; i++) {
            string territoryowner = map->getTerritories()[i]->getOwner();
            if (territoryowner != player ) {
                count = count + 1;
                break;
            }
        }
    }
    if (count == NumberOfPlayers) return false;
    else return true;
}

// Check that players are still valid, remove players that are not
// Validity : must own at least on territory
void GameEngine::checkPlayers() {   
    for (Player* p : player_list) {
        if (p->getNumberOfTerritories() == 0) {
            cout << "Player " << p->getName() << " has been eliminated";
            NumberOfPlayers = NumberOfPlayers - 1; //lowers player count
            player_list.erase(std::remove(player_list.begin(), player_list.end(), p*), player_list.end()); //removes player from player_list
        } 
    }
}

// From Iloggable
string GameEngine::stringToLog() {
    string logString = "STRING FORMED FROM ATTRIBUTES OR STATE OF SUBJECT FOR IT TO BE THE RETURN STRING OF THIS METHOD";
    return logString;
};