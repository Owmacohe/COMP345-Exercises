#pragma once

#include <vector>
#include <iostream>
#include <set>

using namespace std;

#include "../LoggingObserver/LoggingObserver.h"

class Player;
class MapLoader;
class Deck;
class CommandProcessor;
class Map;

enum State {
   null = 0, start = 1, mapLoaded = 2, mapValidated = 3, playersAdded = 4, assignReinforcement = 5, issueOrder = 6, executeOrder = 7, win = 8
};

class GameEngine : public Iloggable, public Subject {
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
        CommandProcessor *getProcessor();
        Map *getMap();
        set<pair<Player*, Player*>> getAlliances();
        bool existingAlliance(Player* p1, Player* p2);
        int *getPlayerOrder();
        int getCurrentPlayer();

        // Mutators
        void setState(State s);
        void setNumberOfPlayers(int x);
        void setEndOfState(bool b);
        void setProcessor(const CommandProcessor &cp);
        void setMap(const Map &m);
        void setAlliances (const  set<pair<Player*, Player*>> all);
        void addAlliances(Player* p1, Player* p2);
        void resetAlliances();
        void setPlayerOrder(int*);
        void setCurrentPlayer(int);

        // Phases, states, and commands
        void startGame();
        void loadMap();
        void validateMap();
        void addPlayer();
        void assignCountries();
        void assignReinforcementPhase();
        void issueOrdersPhase();
        void endIssueOrderPhase(Player* player);
        void executeOrdersPhase();
        void endexecuteOrdersPhase(Player* player);
        void winPhase(Player *p);
        void endPhase();
        void playAgain();

        void mainGameLoop();

        void gameStartupTransitions(string s);
        void gamePlayTransitions(string s, Player *p);
        void gameEndTransitions(string s);

        void startupPhase();

        // Checks
        bool checkForWinner();
        void checkPlayers();

        // From Iloggable
        string stringToLog();
    private:
        State* s;
        int NumberOfPlayers;
        int NumberOfTerritories;
        MapLoader *ml;
        bool phaseEnd;
        Deck *deck;
        vector<Player*> player_list;
        CommandProcessor *processor;
        Map *map;
        set<pair<Player*, Player*>> alliances;
        int *playerOrder;
        int currentPlayer;
};