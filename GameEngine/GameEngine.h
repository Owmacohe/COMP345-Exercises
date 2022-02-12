#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Player;
class MapLoader;
class Deck;

enum State
{
   null = 0, start = 1, maploaded = 2, mapvalidated = 3, playersadded = 4, PLAY= 5
};

class GameEngine {
    public:
        GameEngine() ; // constructor
        GameEngine(GameEngine &gm); //copy constructor
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
        bool isWinner();
        bool playAgain();

    private:
        State* s ;
        int NumberOfPlayers;
        int NumberOfTerritories;
        MapLoader * ml;
        bool phaseEnd;
        Deck* deck;
        vector<Player *> player_list;
};