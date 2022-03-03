#include "GameEngine.h"
#include "../Cards/Cards.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Orders/Orders.cpp"
#include <vector>
#include <iostream>
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
}

// Destructor
GameEngine::~GameEngine() {
    delete s;
    s = NULL;

    delete deck;
    deck = NULL;

    for (Player* p : player_list) {
        delete p;
        p = NULL;
    }
}

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

// Mutators
void GameEngine::setState(State s) { this->s = &s; }
void GameEngine::setNumberOfPlayers(int x) { this->NumberOfPlayers = x; }
void GameEngine::setEndOfState(bool b) { this->phaseEnd = b; }

// Phases, states, and commands
void GameEngine::startGame() {
    *s = start;
    cout << "Welcome to Warzone" << endl;
    cout << "Please enter the number of players" << endl;
    cin >> this->NumberOfPlayers;
    cout<< "end of start phase" << endl;
}

void GameEngine::loadMap() {
    *s = mapLoaded;

    /*
    string mapName;
    cout << "enter map name" << endl;
    cin >> mapName;

    while(mapName != "canada" || mapName != "europe") {
        cout<< "incorrect, please re-enter map name" << endl;
        cin >> mapName;
    }
    
    Map m = ml->load(mapName + ".map");
    */

    cout << "loaded map" << endl;
}

void GameEngine::validateMap() {
    *s = mapValidated;
    cout<< "end of map validated phase" << endl;
};


void GameEngine::addPlayer() { // TODO GABBI (add players one at a time)
    *s = playersAdded;

    for(int i = 0; i < NumberOfPlayers; i++) {
        string name;
        Player *p = new Player;
        cout << "Please enter the player's name" << endl;
        cin >> name;
        p->setName(name);
        player_list.push_back(p);
    }

    cout<< "end of players added phase" << endl;
}

void GameEngine::assignCountries() {
    cout<< "end of assign countries command" << endl;
}

void GameEngine::assignReinforcementPhase() {
    *s = assignReinforcement;
    cout<< "end of assign Reinforcement" << endl;
}

void GameEngine::issueOrders(Player *player) {
    *s = issueOrder;
    cout<< "Issued the order for player " << player->getName() << endl;
}

void GameEngine::endIssueOrderPhase(Player *player) {
    *s = executeOrder;
    cout<< "ended phase issue Orders for player " << player->getName() << endl;
}

void GameEngine::executeOrdersPhase() {

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
    while(deployDoneCount < NumberOfPlayers){
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
    while(playersDone < NumberOfPlayers){
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
    for (int i = 0 ; i<NumberOfPlayers; i++){
        if(player_list[i]->getTerritory().size() == 0)
            lost ++ ;
        if (lost == NumberOfPlayers-1){
            for (int j = 0; j < NumberOfPlayers; j++) {
                if(player_list[j]->getTerritory().size()>0){
                    winPhase(player_list[j]);
                    break;
                }
                break;
            }
        }else assignReinforcementPhase();
    }
}



void GameEngine::endexecuteOrdersPhase(Player *player) {
    *s = assignReinforcement;
    cout << "ended phase execute Order for player " << player->getName() << endl;
}

void GameEngine::winPhase(Player *p) {
    *s = win;
    cout<< "victory for player: " << p->getName() << endl;
}

void GameEngine::endPhase() {
    *s = null;
    cout<< "Thank you for Playing Warzone" << endl;
}

void GameEngine::playAgain() {
    *s = null;
    cout<< "the Game will restart soon" << endl;
}

void GameEngine::gameStartupTransitions(string str) {
    if (str == "loadmap" && (getState() == 1 || getState() == 2)) {
        loadMap();
    }
    else if (str == "validatemap" && getState() == 2) {
        validateMap();
    }
    else if (str == "addplayer" && (getState() ==3 || getState() == 4)){
       addPlayer();
    }
    else if (str == "assigncountries" && getState() ==4){
        assignCountries();
        assignReinforcementPhase();
    }
    else {
        cout << "Invalid command!" << endl;
    }
}

void GameEngine::gamePlayTransitions(string str, Player *p) {
    if (str == "issueorder" && (getState() == 5 || getState() == 6)) {
        issueOrders(p);
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
}

void GameEngine::startupPhase() {
    // use the loadmap <filename> command to select a map from a list of map files as stored in a directory, which results in the map being loaded in the game

    // use the validatemap command to validate the map (i.e. it is a connected graph, etc – see assignment 1)

    // use the addplayer <playername> command to enter players in the game (2-6 players)

    /*
    use the gamestart command to:
        fairly distribute all the territories to the players
        determine randomly the order of play of the players in the game
        give 50 initial armies to the players, which are placed in their respective reinforcement pool
        let each player draw 2 initial cards from the deck using the deck’s draw() method
        switch the game to the play phase
    */
}