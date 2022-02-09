#pragma once
#include <iostream>

using namespace std;


enum State
{
 start = 1, maploaded = 2, mapvalidated = 3, playersadded = 4, PLAY= 5
};
class GameEngine(){
    public:
        GameEngine() ; // constructor
        GameEngine(GameEngine &gm); //copy constructor
        ~GameEngine(); // destructor

        //getters
        State getState();
        int getNumberOfPlayers();
        bool endOfState ();
        //setters
        void setState(State s);
        //phases , states and commands
        void startGame();
        void loadMap();
        void validateMap();
        void addPlayer();
        void setNumberOfPlayers(int x);
        void setEndOfState(bool b);
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







}



