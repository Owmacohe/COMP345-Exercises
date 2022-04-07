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

bool doesContain(vector<int>, int); // Free method to determine whether an int vector contains a given int

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
        State *getState();
        int getNumberOfPlayers();
        bool endOfState ();         // TODO WE DELETE THIS ?
        vector<Player*> getplayer_list();
        CommandProcessor *getProcessor();
        Map *getMap();
        Deck *getDeck();
        set<pair<Player*, Player*>> getAlliances();
        bool existingAlliance(Player*, Player*);
        vector<int> getPlayerOrder();
        int getCurrentPlayer();
        Player* getNeutralPlayer();
        bool getIsTournament();
        int getGameNumber();
        int getMapNumber();
        vector<string> getTournamentResults();
        int getNumberOfTurns();

        // Mutators
        void setState(const State &s);
        void setNumberOfPlayers(int x);
        void setNumberOfTerritories(int x);
        void setEndOfState(bool b);
        void setplayer_list(vector<Player*>);
        void setProcessor(CommandProcessor*);
        void setMap(Map*);
        void setDeck(Deck*);
        void setAlliances (const  set<pair<Player*, Player*>>);
        void addAlliances(Player*, Player*);
        void resetAlliances();
        void setPlayerOrder(vector<int>);
        void setCurrentPlayer(int);
        void setNeutralPlayer(Player* np);
        void setIsTournament(bool);
        void setGameNumber(int);
        void setMapNumber(int);
        void setTournamentResults(vector<string>);
        void setNumberOfTurns(int);

        void assignReinforcementPhase();
        void issueOrdersPhase();
        void endIssueOrderPhase();
        bool hasMoreDeploy(Player*);
        void executeOrdersPhase();
        void endexecuteOrdersPhase();
        void winPhase(Player*);
        void drawPhase();
        void endPhase();
        void playAgain();
        void transition(State);
        bool mainGameLoop();

        void gamePlayTransitions(string, Player*);
        void gameEndTransitions(string);

        void startupPhase(); // Checks to see if a tournament command has been entered, and manages calling startupCommands
        void startupCommands(bool, bool); // Reads (startup) commands sequentially from the console

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
        bool phaseEnd;
        Deck *deck;
        vector<Player*> player_list;
        CommandProcessor *processor;
        Map *map;
        set<pair<Player*, Player*>> alliances;
        vector<int> playerOrder;
        int currentPlayer;
        Player* neutralPlayer;

        // Tournament
        bool isTournament;
        int gameNumber; // Track the game being played
        int mapNumber; // Track the map being played
        vector<string> tournamentResults; // Store the results of each game
        int numberOfTurns; // Track number of turns in current game

};