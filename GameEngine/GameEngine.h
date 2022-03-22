#pragma once

#include <vector>
#include <iostream>
#include <set>
#include <cmath>

using namespace std;

#include "../LoggingObserver/LoggingObserver.h"

class Player;
class MapLoader;
class Deck;
class Hand;
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
        Deck *getDeck();
        set<pair<Player*, Player*>> getAlliances();
        bool existingAlliance(Player*, Player*);
        int *getPlayerOrder();
        int getCurrentPlayer();
        Player* getNeutralPlayer();

        // Mutators
        void setState(State s);
        void setNumberOfPlayers(int x);
        void setEndOfState(bool b);
        void setplayer_list(vector<Player*>);
        void setProcessor(const CommandProcessor &cp);
        void setMap(const Map &m);
        void setDeck(const Deck &d);
        void setAlliances (const  set<pair<Player*, Player*>> all);
        void addAlliances(Player*, Player*);
        void resetAlliances();
        void setPlayerOrder(int*);
        void setCurrentPlayer(int);
        void setNeutralPlayer(Player* np);

        // Phases, states, and commands
        /*
        void startGame();
        void loadMap();
        void validateMap();
        void addPlayer();
        void assignCountries();
        */
        void assignReinforcementPhase();
        void issueOrdersPhase();
        void endIssueOrderPhase(Player*);
        bool hasMoreDeploy(Player*);
        void executeOrdersPhase();
        void endexecuteOrdersPhase(Player*);
        void winPhase(Player*);
        void endPhase();
        void playAgain();

        void mainGameLoop();

        //void gameStartupTransitions(string s);
        void gamePlayTransitions(string, Player*);
        void gameEndTransitions(string);

        void startupPhase(); // Reads (startup) commands sequentially from the console

        // Checks
        bool checkForWinner();
        void checkPlayers();
        int checkCardInHand(string, Hand*);
        bool equalsIgnoreCase(string, string);

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
        Player* neutralPlayer;
};