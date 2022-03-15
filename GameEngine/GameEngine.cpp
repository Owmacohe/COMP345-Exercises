#include "GameEngine.h"
#include "../Cards/Cards.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../LoggingObserver/LoggingObserver.h"
#include "../CommandProcessing/CommandProcessing.h"

#include "math.h"

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
    neutralPlayer = new Player();
    neutralPlayer->setName("Neutral");

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

    delete neutralPlayer;
    neutralPlayer = NULL;
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
Player* GameEngine::getNeutralPlayer() {return neutralPlayer;}

// Mutators
void GameEngine::setState(State s) { this->s = &s; }
void GameEngine::setNumberOfPlayers(int x) { this->NumberOfPlayers = x; }
void GameEngine::setEndOfState(bool b) { this->phaseEnd = b; }
void GameEngine::setplayer_list(vector<Player*> pl){player_list = pl;}
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
void GameEngine::setNeutralPlayer(Player* np) {neutralPlayer = np;};

// THE FOLLOWING METHODS ARE UNNECESSARY NOW, BUT WE SHOULD KEEP THEM COMMENTED JUST IN CASE

/*
// Phases, states, and commands
void GameEngine::startGame() {
    *s = start;
    cout << "Welcome to Warzone" << endl;
    cout << "Please enter the number of players" << endl;
    cin >> this->NumberOfPlayers;
    cout << "end of start phase" << endl;

   startupPhase();
}

void GameEngine::loadMap() {
    *s = mapLoaded;

    string mapName;
    cout << "enter map name" << endl;
    cin >> mapName;

    while(mapName != "canada" || mapName != "europe") {
        cout << "incorrect, please re-enter map name" << endl;
        cin >> mapName;
    }
    
    Map m = ml->load(mapName + ".map");

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
*/

void GameEngine::assignReinforcementPhase() {
    *s = assignReinforcement;
    cout << "Assign reinforcement phase" << endl;

    // Adding the reset of alliances
    //resetAlliances();

    Player* p = player_list.at(currentPlayer);

    int num = floor((p->getNumberOfTerritories())/3);
    if (num < 3) p->addToReinforcePool(3); // Minimum number of armies per turn for any player is 3
    else p->addToReinforcePool(num);

    vector<Territory*> territoriesByContinent;

    string* Continents = map->getContinents();
    for (int i = 0; i < Continents->size(); i++) { // Loop through all continents
        bool flag = true;
        territoriesByContinent = map->getContinentTerritories(Continents[i]);
        for (Territory * t : territoriesByContinent){ // Loop through territories in each continent to check if they belong to player
            if(!(t->getOwner()->getName() == p->getName())) {
                flag = false; // Break and set flag false if player does not own territory
                break;
            }
        }
        if (flag == false) { continue; }
        else {
            string bonus = map->getContinentBonuses()[i];
            p->addToReinforcePool(stoi(bonus));
        }
    }
    cout << "End of assign reinforcement" << endl;
}

void GameEngine::issueOrdersPhase() {
    *s = issueOrder;
    string input;
    string response;

    Player* p = player_list.at(currentPlayer);

    cout << "Issuing the orders for player " << p->getName() << endl;
    // Only issue deploy orders while the players reinforcement pool contains armies
    cout << "Issueing deploy orders" << endl;
    while (p->getReinforcePool() != 0) {
        p->issueOrder("deploy");
    }
    // Issue advance orders
    cout << "Issueing advance orders" << endl;
    do {
        cout << "Would " << p->getName() << " like to issue an Advance order ? y/n " << endl;
        cin >> input;
        if (equalsIgnoreCase(input, "y") || equalsIgnoreCase(input, "yes")) {
            p->issueOrder("advance");
            // MJ said that checking if an advance is attacking or defending is done in orders
        }
        else break;
    } while (equalsIgnoreCase(input, "y") || equalsIgnoreCase(input, "yes"));
 
    // Issue card orders
    cout << "Issueing card orders" << endl;
    do {
        cout << "Would " << p->getName() << " like to play any cards ? y/n " << endl;
        cin >> input;
        if (equalsIgnoreCase(input, "y") || equalsIgnoreCase(input, "yes")) {
            cout << "The following is " << p->getName() << " hand" << endl;
            cout << p->getHand() << endl;
            cout << "Which card would you like to play ?" << endl;
            cin >> response;
            int index = checkCardInHand(response, p->getHand());
            if (index != -1) p->getHand()->playCard(index, *deck, *p->getOrder());
        }
        else break;
    } while (equalsIgnoreCase(input, "y") || equalsIgnoreCase(input, "yes"));

    endIssueOrderPhase(p);
}

void GameEngine::endIssueOrderPhase(Player *player) {
    *s = executeOrder;
    cout << "End phase issue orders for player " << player->getName() << endl;
}

void GameEngine::executeOrdersPhase() {
    // First , adding all deploy orders into a separate list and removing them from the original player's lists
    cout << "Executing Deploy Order" << endl;
    for (int i = 0; i < player_list.size(); i++) {
        for (int j = 0; j < player_list[i]->getOrder()->getOrderList().size(); j++) {
            if (player_list[i]->getOrder()->getOrderList()[j]->description == "Deploy") {
                  player_list[i]->getDeployList()->addOrder(player_list[i]->getOrder()->getOrderList().at(j));
                  player_list.at(i)->getOrder()->remove(j);
            }
        }
    }
    // To execute and remove the deploy orders
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
    // To execute the rest of the orders on each player's list
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
}

void GameEngine::endexecuteOrdersPhase(Player *player) {
    *s = assignReinforcement;
    cout << "End phase execute Order for player " << player->getName() << endl;
}

void GameEngine::winPhase(Player *p) {
    *s = win;
    cout << "Victory for player: " << p->getName() << endl;
}

void GameEngine::endPhase() {
    *s = null;
    cout << "Thank you for Playing Warzone" << endl;
}

void GameEngine::playAgain() {
    *s = null;
    cout << "The Game will restart soon" << endl;
}

// THE FOLLOWING METHOD IS UNNECESSARY NOW, BUT WE SHOULD KEEP IT COMMENTED JUST IN CASE

/*
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
*/

void GameEngine::gamePlayTransitions(string str, Player *p) {
    if (str == "issueorder" && (getState() == 5 || getState() == 6)) {
        issueOrdersPhase();
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

// Reads (startup) commands sequentially from the console
void GameEngine::startupPhase() {
    *s = start;

    cout << "Welcome to Warzone" << endl;

    while (*s < 5) {
        cout << "Enter a command: " << endl;

        processor->getCommand();

        Command temp = processor->getCommands()[processor->commandsLength - 1];

        string effect = "";

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
                // Use the loadmap <filename> command to select a map from a list of map files as stored in a directory, which results in the map being loaded in the game

                MapLoader loader;
                Map m = Map(loader.load(word2));

                if (m.isGoodMap) {
                    *map = m;
                    effect = "Loaded Map: " + map->getName();
                    cout << effect << "!" << endl;
                    *s = mapLoaded;
                }
                else {
                    effect = "Unable to load Map";
                    cout << effect << "!" << endl;
                }
            }
            else if (word1 == "validatemap") {
                // Use the validatemap command to validate the map (i.e. it is a connected graph, etc – see assignment 1)

                if (map->validate()) {
                    effect = "Validated Map: " + map->getName();
                    cout << effect << "!" << endl;
                    *s = mapValidated;
                }
                else {
                    effect = "Unable to validate Map";
                    cout << effect << "!" << endl;
                }
            }
            else if (word1 == "addplayer") {
                // Use the addplayer <playername> command to enter players in the game (2-6 players)

                if (word2.length() > 0 && word2[0] != ' ' && word2[word2.length() - 1] != ' ') {
                    Player *p;
                    p->setName(word2);
                    player_list.push_back(p);

                    effect = "Added Player: " + p->getName();
                    cout << effect << "!" << endl;

                    *s = playersAdded;
                }
                else {
                    effect = "Unable to add Player";
                    cout << effect << "!" << endl;
                }
            }
            else if (word1 == "gamestart") {
               // Fairly distribute all the territories to the players

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

                effect = "Distributed Territories to Players";

                // Determine randomly the order of play of the players in the game

                int *tempOrder = new int[player_list.size()];

                for (int j = 0; j < player_list.size(); j++) {
                    tempOrder[j] = rand() % (player_list.size() - j) + j;
                }

                setPlayerOrder(tempOrder);

                effect += ", randomly determined the order of playing order";

                for (Player* k : player_list) {
                    // Give 50 initial armies to the players, which are placed in their respective reinforcement pool
                    k->addToReinforcePool(50);

                    // Let each player draw 2 initial cards from the deck using the deck’s draw() method
                    k->getHand()->drawCard(*deck);
                    k->getHand()->drawCard(*deck);
                }

                effect += ", gave 50 armies to each Player, and drew 2 cards for each Player";

                // Switch the game to the play phase

                *s = assignReinforcement;
            }
            else if (word1 == "replay") {
                // TODO restart the game
            }
            else if (word1 == "win") {
                // TODO end the game
            }
        }

        temp.saveEffect(effect);
    }

    // ALSO ADD GameEngine Pointer to attribute to Order Class
    // Order::setGameEngine(new );

    notify(this); // FROM SUBJECT
}

// Main game loop, includes reinforcement phase, issue order phase, execute order phase
void GameEngine::mainGameLoop() {
    bool playing = true;
    string input;
    while (playing == true) {
        for (int i = 0; i < NumberOfPlayers; i++) {
            Player *p = player_list.at(playerOrder[i]);
        
            assignReinforcementPhase(); // Begin reinforcement phase
            issueOrdersPhase(); // Begin issue orders phase
            executeOrdersPhase(); // Begin execute orders phase
            checkPlayers(); // Check if any players need to be removed
            playing = !checkForWinner(); // Check for winner
        }
        resetAlliances(); // Reset Alliances
    }

    // TODO need to use Commands to check for "replay" and "win"

    cout << "Would you like to play again ? y/n " << endl;
    cin >> input;
    if (equalsIgnoreCase(input, "y") || equalsIgnoreCase(input, "yes")) { 
        playAgain();
        *s = start; // Switch to start up for replay
    }
    else endPhase();
}

// Check if a player has won by looping through territories and checking owner
bool GameEngine::checkForWinner() {
    int lost = 0;
    for (Player* p : player_list) { 
        string player = p->getName();
        for (int i = 0; i < map->territoriesLength; i++) {
            string owner = map->getTerritories()[i].getOwner()->getName();
            if (owner != player ) {
                lost = lost + 1;
                break; 
            }
        }
        if (lost == 0) {
            winPhase(p);
            return true;
        }
    }
    return false;
}

// Check that players are still valid, remove players that are not
// Validity : must own at least on territory
void GameEngine::checkPlayers() {   
    for (Player* p : player_list) {
        if (p->getNumberOfTerritories() == 0) {
            cout << "Player " << p->getName() << " has been eliminated";
            NumberOfPlayers = NumberOfPlayers - 1; //lowers player count
            player_list.erase(std::remove(player_list.begin(), player_list.end(), p), player_list.end()); //removes player from player_list
        } 
    }
}

// Check that a card type is in a specific hand
int GameEngine::checkCardInHand(string type, Hand* h) {
    int index = 0; //returns index of card in hand, -1 if card is not in hand
    for (Card* c : h->hand) {
        if (equalsIgnoreCase(c->getType(), type)) return index;
        index = index + 1;
    }
    return -1;
}

bool GameEngine::equalsIgnoreCase(string s1, string s2) {
   // Change to lower case
   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
   if (s1 == s2) return true;
   else return false;
}

// From Iloggable
string GameEngine::stringToLog() {
    string enumStates[] = {"null", "start", "mapLoaded", "mapValidated", "playersAdded", "assignReinforcement", "issueOrder", "executeOrder", "win"};
    string logString = "Game Engine now at the " + enumStates[*s] + "state. \n";
    return logString;
};