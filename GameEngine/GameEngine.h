#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Player;
class MapLoader;
class Deck;

enum State
{
   null = 0, start = 1, mapLoaded = 2, mapValidated = 3, playersAdded = 4, assignReinforcement = 5, issueOrder = 6, executeOrder = 7, win = 8
};

class GameEngine {

    public:
        GameEngine() ; // constructor
        GameEngine(const GameEngine &gm); //copy constructor
        ~GameEngine(); // destructor
        GameEngine& operator = (const GameEngine& gm); // Assignment Operator

        //getters
        State getState();
        int getNumberOfPlayers();
        bool endOfState ();

        //setters
        void setState(State s);
        void setNumberOfPlayers(int x);
        void setEndOfState(bool b);

        //phases , states and commands
        void startGame();
        void loadMap();
        void validateMap();
        void addPlayer();
        void executeOrdersPhase(Player* player);
        void issueOrdersPhase(Player* player);
        void ReinforcementPhase();

    private:
        State* s ;
        int NumberOfPlayers;
        int NumberOfTerritories;
        MapLoader *ml;
        bool phaseEnd;
        Deck* deck;
        vector<Player*> player_list;
};