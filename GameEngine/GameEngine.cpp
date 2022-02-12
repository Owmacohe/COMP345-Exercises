#include "GameEngine.h"
#include "../Cards/Cards.h"
#include "../Player/Player.h"
#include "Map/Map.h"
#include <vector>
#include <string>
using namespace std;
GameEngine::GameEngine(){
    *s = null;
    NumberOfPlayers = 0;
    NumberOfTerritories = 0;
    deck = new Deck();
    player_list = vector<Player*>();
} ; // constructor
GameEngine::GameEngine(const GameEngine &gm){
    s = gm.s;
    NumberOfPlayers = gm.NumberOfPlayers;
    NumberOfTerritories = gm.NumberOfTerritories;
    this->deck = new Deck(*(gm.deck));
    for (Player* p : gm.player_list) {
        this->player_list.push_back(new Player(*p));
    }

}; //copy constructor
GameEngine::~GameEngine(){
    delete s;
    s = NULL;

    delete deck;
    deck = NULL;

    for (Player* p : player_list) {
        delete p;
        p = NULL;
    }

} // destructor



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
    *s = maploaded;
    string map;
    cout<< "enter map name" << endl;
    cin >> map;
    while(map != "canada" || map != "europe"){
        cout<< "incorrect, please re-enter map name" << endl;
        cin >> map;
    }
    Map * m = new Map();
    *m = ml->load(map + ".map");
    cout<< "end of load map phase" << endl;
}
void GameEngine::validateMap(){
    //
    cout<< "end of map validated phase" << endl;
};


void GameEngine::addPlayer(){
    *s = playersadded;
    for(int i =0 ; i<NumberOfPlayers ; i++){
        string name;
        Player *p = new Player();
        cout << "Please enter the player's name" << endl;
        cin >> name;
        p->setName(name);
        player_list.push_back (p);
    }
    cout<< "end of add player phase" << endl;

}

void GameEngine::issueOrdersPhase(Player* player){
    *s = issueorder;
    cout<< "end of issue orders phase" << endl;

}
void GameEngine::executeOrdersPhase(Player* player){
    *s = executingorder;
    cout<< "end of execute orders phase" << endl;
}
void GameEngine::ReinforcementPhase(){
    *s = reinforcement;
    cout<< "end of add player phase" << endl;

};

