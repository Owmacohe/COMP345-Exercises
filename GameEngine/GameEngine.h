#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Player;
class MapLoader;
class Deck;

enum State {
   null = 0, start = 1, mapLoaded = 2, mapValidated = 3, playersAdded = 4, assignReinforcement = 5, issueOrder = 6, executeOrder = 7, win = 8
};

class GameEngine {
    public:
        GameEngine() ; // Constructor
        GameEngine(const GameEngine &gm); // Copy constructor
        ~GameEngine(); // Destructor
        GameEngine& operator = (const GameEngine& gm); // Assignment operator
        friend ostream& operator<<(ostream& os, const GameEngine& gm); // Stream insertion operator

        // Accessors
        State getState();
        int getNumberOfPlayers();
        bool endOfState ();
        vector<Player*> getplayer_list();

        // Mutators
        void setState(State s);
        void setNumberOfPlayers(int x);
        void setEndOfState(bool b);

        // Phases, states, and commands
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

        void startupPhase();
    private:
        State* s;
        int NumberOfPlayers;
        int NumberOfTerritories;
        MapLoader *ml;
        bool phaseEnd;
        Deck* deck;
        vector<Player*> player_list;
};