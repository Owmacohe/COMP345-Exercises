#include "GameEngine.h"
#include "../Cards/Cards.h"
#include "../Player/Player.h"
#include "../Map/Map.h"

// constructor
GameEngine::GameEngine(){
    *s = null;
    NumberOfPlayers = 0;
    NumberOfTerritories = 0;
    deck = new Deck();
    player_list = vector<Player*>();
}

//copy constructor
GameEngine::GameEngine(const GameEngine &gm){
    s = gm.s;
    NumberOfPlayers = gm.NumberOfPlayers;
    NumberOfTerritories = gm.NumberOfTerritories;
    this->deck = new Deck(*(gm.deck));
    for (Player* p : gm.player_list) {
        this->player_list.push_back(new Player(*p));
    }
}

// destructor
GameEngine::~GameEngine(){
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
GameEngine& operator = (const GameEngine& gm) {
    //TODO
};

//getters
State GameEngine::getState(){return *s;}
int GameEngine::getNumberOfPlayers(){return NumberOfPlayers;}
bool GameEngine::endOfState (){return phaseEnd;}

//setters
void GameEngine::setState(State s){this->s = &s;}
void GameEngine::setNumberOfPlayers(int x){this->NumberOfPlayers = x;}
void GameEngine::setEndOfState(bool b){this->phaseEnd = b;}

//phases , states and commands
void GameEngine::startGame(){
    *s = start;
    cout << "Welcome to Warzone" << endl;
    cout << "Please enter the number of players" << endl;
    cin >> this->NumberOfPlayers;
    cout<< "end of start phase" << endl;

}
void GameEngine::loadMap(){
    *s = mapLoaded;
    string map;
    cout<< "enter map name" << endl;
    cin >> map;
    while(map != "canada" || map != "europe"){ //TODO : Owen does this make sense with yours?
        cout<< "incorrect, please re-enter map name" << endl;
        cin >> map;
    }
    Map * m = new Map();
    *m = ml->load(map + ".map");
    cout<< "end of load map phase" << endl;
}
void GameEngine::validateMap(){
    //TODO call Owen's method
    cout<< "end of map validated phase" << endl;
};


void GameEngine::addPlayer(){
    *s = playersAdded;
    for(int i =0 ; i<NumberOfPlayers ; i++){
        string name;
        Player *p = new Player();
        cout << "Please enter the player's name" << endl;
        cin >> name;
        p->setName(name);
        player_list.push_back (p);
    }
    cout<< "end of players added phase" << endl;

}

void GameEngine::issueOrdersPhase(Player* player){
    *s = issueOrder;
    cout<< "end of issue orders phase" << endl;
}

void GameEngine::executeOrdersPhase(Player* player){
    *s = executeOrder;
    cout<< "end of execute orders phase" << endl;
}

void GameEngine::ReinforcementPhase(){
    *s = assignReinforcement;
    cout<< "end of assign Reinforcement" << endl;

};

