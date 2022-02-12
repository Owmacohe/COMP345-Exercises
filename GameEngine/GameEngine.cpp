#include "GameEngine.h"
#include <vector>
#include <string>
using namespace std;
GameEngine::GameEngine(){
    s = null;
    NumberOfPlayers = 0;
    NumberOfTerritories = 0;
    deck = new Deck();
    player_list = vector<Player*>();
} ; // constructor
GameEngine::GameEngine(const GameEngine &gm){
    s = gm.s;
    NumberOfPlayers = gm.NumberOfPlayers;
    NumberOfTerritories = gm.NumberOfTerritories;
    this->deck = new Deck(*(p.hand));
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
GameEngine::State getState(){return s;};
int GameEngine::getNumberOfPlayers(){return NumberOfPlayers};
bool GameEngine::endOfState (){return phaseEnd};

//setters
void GameEngine::setState(State s){this->s = s;}
void GameEngine::setNumberOfPlayers(int x){this->NumberOfPlayers = x;}
void GameEngine::setEndOfState(bool b){this->phaseEnd = b;}
//phases , states and commands
void GameEngine::startGame(){
    cout << "Welcome to Warzone" << endl;
    cout << "Please enter the number of players" << endl;
    cin >> this->NumberOfPlayers
};
void GameEngine::loadMap();
void GameEngine::validateMap();


void GameEngine::addPlayer(){
    for(int i =0 ; i<NumberOfPlayers ; i++){
        string name;
        Player *  p;
        cout << "Please enter the player's name" << endl;
        cin >> name;
        p.setName(name);
        player_list.push_back (p);
    }

};

void GameEngine::issueOrdersPhase(Player* player);
void GameEngine::executeOrdersPhase(Player* player);
void GameEngine::ReinforcementPhase();
bool GameEngine::isWinner();
bool GameEngine::playAgain();