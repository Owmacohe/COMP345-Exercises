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
        vector<Player*> getplayer_list();

        //setters
        void setState(State s);
        void setNumberOfPlayers(int x);
        void setEndOfState(bool b);

        //phases , states and commands
        void startGame();
        void loadMap();
        void validateMap();
        void addPlayer();
        void assignCountries();
        void assignReinforcementPhase();
        void issueOrders(Player* player);
        void endIssueOrderPhase(Player* player);
        void executeOrders(Player* player);
        void endexecuteOrdersPhase(Player* player);
        void winPhase(Player *p);
        void endPhase();
        void playAgain();

        void gameStartupTransitions(string s);
        void gamePlayTransitions(string s, Player *p);
        void gameEndTransitions(string s);


    private:
        State* s ;
        int NumberOfPlayers;
        int NumberOfTerritories;
        MapLoader *ml;
        bool phaseEnd;
        Deck* deck;
        vector<Player*> player_list;

};