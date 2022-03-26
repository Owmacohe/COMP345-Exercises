#include "GameEngine.h"
#include "../Cards/Cards.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../CommandProcessing/CommandProcessing.h"

class OrdersList;
class Player;

// Default constructor
GameEngine::GameEngine() {
    s = new State;
    *s = null;
    NumberOfPlayers = 0;
    NumberOfTerritories = 0;
    deck = new Deck();
    player_list = vector<Player*>();
    map = new Map();
    alliances = set<pair<Player*, Player*>>();

    // Add Neutral Player to Game
    neutralPlayer = new Player();
    neutralPlayer->setName("Neutral");

    // Attributes not initialized, CONFIRM WITH TEAM
//    MapLoader *ml;
//    bool phaseEnd;
//    CommandProcessor *processor;

}

// Copy constructor
GameEngine::GameEngine(const GameEngine &gm) {
    s = gm.s;
    NumberOfPlayers = gm.NumberOfPlayers;
    NumberOfTerritories = gm.NumberOfTerritories;
    this->deck = new Deck(*(gm.deck));

    for (Player* p : gm.player_list) {
        this->player_list.push_back(new Player(*p));
    }
    Map *map = new Map(*gm.map);

    alliances = set<pair<Player*, Player*>>();
    for(auto x : gm.alliances) {
        pair<Player*, Player*> pairCopied = make_pair(new Player(*x.first), new Player(*x.second));
        alliances.insert(pairCopied);
    }

    // Attributes not initialized / Destroyed, CONFIRM WITH TEAM
//    MapLoader *ml;
//    bool phaseEnd;
//    CommandProcessor *processor;
}

// Destructor
GameEngine::~GameEngine() {
    delete s;
    s = NULL;

    delete ml;
    ml = NULL;

    delete deck;
    deck = NULL;

    for (Player* p : player_list) {
        delete p;
        p = NULL;
    }

    delete processor;
    processor = NULL;

    delete[] map;
    map = NULL;

    for(auto x : alliances) {
        x.first = NULL;
        x.second = NULL;
    }
    alliances.clear();

    delete neutralPlayer;
    neutralPlayer = NULL;
}
// Attributes not initialized / Destroyed, CONFIRM WITH TEAM
//    bool phaseEnd;

// Assignment operator
GameEngine& GameEngine::operator = (const GameEngine& gm) {
    this->s = gm.s;
    NumberOfPlayers = gm.NumberOfPlayers;
    NumberOfTerritories = gm.NumberOfTerritories;
    this->ml = gm.ml;
    phaseEnd = gm.phaseEnd;
    this->deck = gm.deck;

    for (Player* p : gm.player_list) {
        this->player_list.push_back(p);
    }

    return *this;
    // Attributes not initialized / Destroyed, CONFIRM WITH TEAM
//    MapLoader *ml;
//    bool phaseEnd;
//    CommandProcessor *processor;
//    alliances = set<pair<Player*, Player*>>();
//    Map *map;
};

// Stream insertion operator
ostream& operator<<(ostream &os, const GameEngine& gm) {
    string p = "";
    for (Player* i : gm.player_list) {
        p += (*i).getName() + " | ";
    }

    return os <<
        "GAME ENGINE: Current state: "<< gm.s <<
        "\n    Players (" << gm.NumberOfPlayers<< "): " <<endl<< p.substr(0, p.length() - 2) <<
        "\n    Number of Territories : (" << gm.NumberOfTerritories << ")" << endl;
}

// Accessors
State *GameEngine::getState() { return s; }
int GameEngine::getNumberOfPlayers() { return NumberOfPlayers; }
bool GameEngine::endOfState() { return phaseEnd; }
vector<Player*> GameEngine::getplayer_list() { return player_list; }
CommandProcessor *GameEngine::getProcessor() { return processor; }
Map *GameEngine::getMap() { return map; }
Deck *GameEngine::getDeck() { return deck; }
set<pair<Player*, Player*>> GameEngine::getAlliances() {return alliances;};
bool GameEngine::existingAlliance(Player* p1, Player* p2) {
    for(auto x : alliances) {
        if(x.first == p1) {
            if (x.second == p2)
                return true;
        }
        else if(x.first == p2) {
            if (x.second == p1)
                return true;
        }
    }
    return false;
}
vector<int> GameEngine::getPlayerOrder() { return playerOrder; }
Player* GameEngine::getNeutralPlayer() {return neutralPlayer;}

// Mutators
void GameEngine::setState(const State &st) { *s = st; }
void GameEngine::setNumberOfPlayers(int x) { this->NumberOfPlayers = x; }
void GameEngine::setNumberOfTerritories(int x) { this->NumberOfTerritories = x; }
void GameEngine::setEndOfState(bool b) { this->phaseEnd = b; }
void GameEngine::setplayer_list(vector<Player*> pl){player_list = pl;}
void GameEngine::setProcessor(CommandProcessor *cp) { processor = cp; }
void GameEngine::setMap(const Map &m) { *map = m; }
void GameEngine::setDeck(const Deck& d){ *deck = d;}
void GameEngine::setAlliances(const set<pair<Player *, Player *>> all) {alliances = all;}
void GameEngine::addAlliances(Player* p1, Player* p2) {alliances.insert(make_pair(p1,p2));}
void GameEngine::resetAlliances() {
    for(auto x : alliances) {
        x.first = NULL;
        x.second = NULL;
    }
    alliances.clear();
}
void GameEngine::setPlayerOrder(vector<int> po) {
    playerOrder = vector<int>();

    for (int i : po) {
        playerOrder.push_back(i);
    }
}
void GameEngine::setNeutralPlayer(Player* np) {neutralPlayer = np;};

// THE FOLLOWING METHODS ARE UNNECESSARY NOW, BUT WE SHOULD KEEP THEM COMMENTED JUST IN CASE

/*
// Phases, states, and commands
void GameEngine::startGame() {
    *s = start;
    cout << "Welcome to Warzone" << endl;
    cout << "Please enter the number of players" << endl;
    cin >> this->NumberOfPlayers;
    cout << "end of start phase" << endl;

   startupPhase();
}

void GameEngine::loadMap() {
    *s = mapLoaded;

    string mapName;
    cout << "enter map name" << endl;
    cin >> mapName;

    while(mapName != "canada" || mapName != "europe") {
        cout << "incorrect, please re-enter map name" << endl;
        cin >> mapName;
    }

    Map m = ml->load(mapName + ".map");

    cout << "Loaded map" << endl;
}

void GameEngine::validateMap() {
    *s = mapValidated;
    cout << "End of map validated phase" << endl;
}

void GameEngine::addPlayer() {
    *s = playersAdded;

    for(int i = 0; i < NumberOfPlayers; i++) {
        string name;
        Player *p = new Player;
        cout << "Please enter the player's name" << endl;
        cin >> name;
        p->setName(name);
        player_list.push_back(p);
    }

    cout << "End of players added phase" << endl;
}

void GameEngine::assignCountries() {
    cout << "End of assign countries command" << endl;
}
*/

void GameEngine::assignReinforcementPhase() {
    *s = assignReinforcement;
    cout << "Assign reinforcement phase" << endl;
    for (int i = 0; i < NumberOfPlayers; i++) {
        Player *p = player_list.at(playerOrder[i]);
        //cout<<p->getName()<<": "<<p->getNumberOfTerritories()<<endl;
        int num = floor((p->getNumberOfTerritories())/3);

        if (num < 3) p->addToReinforcePool(3); // Minimum number of armies per turn for any player is 3
        else p->addToReinforcePool(num);

        vector<Territory*> territoriesByContinent;
        int continent_track = 0;
        for (string continent : map->getContinents()) { // Loop through all continents
            bool flag = true;
            territoriesByContinent = map->getContinentTerritories(continent);
            for (Territory *t : territoriesByContinent) { // Loop through territories in each continent to check if they belong to player
                if(!(t->getOwner()->getName() == p->getName())) {
                    flag = false; // Break and set flag false if player does not own territory
                    break;
                }
            }
            if (flag == false) { continue; }
            else {
                int bonus = map->getContinentBonuses().at(continent_track);
                p->addToReinforcePool(bonus);
            }
            continent_track = continent_track+1;
        }
    }
    cout << "End of assign reinforcement" << endl;
}

void GameEngine::issueOrdersPhase() {
    *s = issueOrder;
    string input;
    string response;
    int deployed = 0;
    int hasMoreTroops = 0;
    // Rubric says: Each player's issueOrder() method is called in round-robin fashion during the issue orders phase.
    for (int i = 0; i < NumberOfPlayers; i++) {
        Player *p = player_list.at(playerOrder[i]);

        cout << "Issuing the orders for player " << p->getName() << endl;

        // Only issue deploy orders while the players reinforcement pool contains armies
        int hasMoreTroops = p->getReinforcePool();
        if (hasMoreTroops > 0)  cout << "Issueing deploy orders" << endl;
        for (int i = 0; i < hasMoreTroops; i++) {
            p->issueOrder("deploy");
            p->setReinforcementPool(p->getReinforcePool()-1);
            cout<<"deploy of army "<<i+1<<"/"<<hasMoreTroops<<" issued"<<endl;
        }

        // Issue advance orders
        cout << p->getName() << "'s turn" <<endl;
        cout << "Issueing advance orders" << endl;
        do {
            cout << "Would " << p->getName() << " like to issue an Advance order ? y/n " << endl;
            cin >> input;
            if (equalsIgnoreCase(input, "y") || equalsIgnoreCase(input, "yes")) {
                p->issueOrder("advance");
                // MJ said that checking if an advance is attacking or defending is done in orders
            } else break;
        } while (equalsIgnoreCase(input, "y") || equalsIgnoreCase(input, "yes"));
        // Issue card orders
        cout << "Issueing card orders" << endl;
        do {
            cout << "Would " << p->getName() << " like to play any cards ? y/n " << endl;
            cin >> input;
            if (equalsIgnoreCase(input, "y") || equalsIgnoreCase(input, "yes")) {
                cout << "The following is " << p->getName() << " hand" << endl;
                cout << *(p->getHand()) << endl;
                cout << "Which card would you like to play ?" << endl;
                cin >> response;
                int index = checkCardInHand(response, p->getHand());
                if (index != -1) p->getHand()->playCard(index, *deck, *p->getOrder());
                else cout << p->getName() << " does not have that card type in hand, and therefore it cannot be played y";
            } else break;
        } while (equalsIgnoreCase(input, "y") || equalsIgnoreCase(input, "yes"));
        endIssueOrderPhase(p);
    }
}

void GameEngine::endIssueOrderPhase(Player *player) {
    *s = executeOrder;
    cout << "End phase issue orders for player " << player->getName() << endl;
}

bool GameEngine::hasMoreDeploy(Player *p) {
    for (Order * o : p->getOrder()->getOrderList()){
        if (o->getDescription() == "Deploy")
            return true;
    }
    return false;
}

void GameEngine::executeOrdersPhase() {
    // First , adding all deploy orders into a separate list and removing them from the original player's lists
    cout << "Executing Deploy Order" << endl;

    int playersWithoutDeploy = 0;
    int playersWithoutOrders = 0;
    bool hasMoreDeployOrders = true;
    bool allOrdersDone = false;

    // avoiding the extra deploy list in player waiting on testing
    while (hasMoreDeployOrders == true ){
        // this loop will loop based on the playing order
        for (int i = 0; i < NumberOfPlayers; i++) {
            Player *p = player_list.at(playerOrder[i]);
            for(int i =0 ; i<p->getOrder()->getOrderList().size(); i++) {
                if (p->getOrder()->getOrderList().at(i)->getDescription() == "Deploy") {
                    p->getOrder()->getOrderList().at(i)->execute();
                    p->getOrder()->remove(i);
                    break;
                }

            }

        }
        for (int i = 0; i < NumberOfPlayers; i++) {
            Player *p = player_list.at(playerOrder[i]);
            if (!hasMoreDeploy(p))
                playersWithoutDeploy++;
        }
        if (playersWithoutDeploy == NumberOfPlayers)
            hasMoreDeployOrders = false;
        else
            playersWithoutDeploy = 0;
    }
    while (allOrdersDone == false ){
        for (int i = 0; i < NumberOfPlayers; i++) {
            Player *p = player_list.at(playerOrder[i]);
            for(int i =0 ; i<p->getOrder()->getOrderList().size(); i++) {
                    p->getOrder()->getOrderList().at(i)->execute();
                    p->getOrder()->remove(i);
                    break;
            }
        }
        for (int i = 0; i < NumberOfPlayers; i++) {
            Player *p = player_list.at(playerOrder[i]);
            if (p->getOrder()->getOrderList().empty())
                playersWithoutOrders ++;
        }
        if (playersWithoutOrders == NumberOfPlayers)
            allOrdersDone = true;
        else
            playersWithoutOrders = 0;
    }






//    for (int i = 0; i < player_list.size(); i++) {
//        for (int j = 0; j < player_list[i]->getOrder()->getOrderList().size(); j++) {
//            if (player_list[i]->getOrder()->getOrderList()[j]->description == "Deploy") {
//                  player_list[i]->getDeployList()->addOrder(player_list[i]->getOrder()->getOrderList().at(j));
//                  player_list.at(i)->getOrder()->remove(j);
//            }
//        }
//    }
//    // To execute and remove the deploy orders
//    int  deployDoneCount =0;
//    while(deployDoneCount < NumberOfPlayers) {
//        deployDoneCount =0;
//        for (int i = 0; i < player_list.size(); i++) {
//            if (!player_list[i]->getDeployList()->getOrderList().empty()) {
//                player_list[i]->getDeployList()->getOrderList().at(i)->execute();
//                player_list[i]->getOrder()->remove(i);
//
//            } else deployDoneCount++;
//        }
//    }
//    // To execute the rest of the orders on each player's list
//    int  playersDone =0;
//    while(playersDone < NumberOfPlayers) {
//        playersDone =0;
//        for (int i = 0; i < player_list.size(); i++) {
//            if (!player_list[i]->getOrder()->getOrderList().empty()) {
//                player_list[i]->getOrder()->getOrderList().at(i)->execute();
//                player_list[i]->getOrder()->remove(i);
//
//            } else {
//
//                playersDone++;
//            }
//        }
//    }
}

void GameEngine::endexecuteOrdersPhase(Player *player) {
    *s = assignReinforcement;
    cout << "End phase execute Order for player " << player->getName() << endl;
}

void GameEngine::winPhase(Player *p) {
    *s = win;
    cout << "Victory for player: " << p->getName() << endl;
}

void GameEngine::endPhase() {
    *s = null;
    cout << "Thank you for Playing Warzone" << endl;
}

void GameEngine::playAgain() {
    *s = null;
    cout << "The Game will restart soon" << endl;
}

// THE FOLLOWING METHOD IS UNNECESSARY NOW, BUT WE SHOULD KEEP IT COMMENTED JUST IN CASE

/*
void GameEngine::gameStartupTransitions(string str) {
    if (str == "loadmap" && (getState() == 1 || getState() == 2)) {
        loadMap();
    }
    else if (str == "validatemap" && getState() == 2) {
        validateMap();
    }
    else if (str == "addplayer" && (getState() ==3 || getState() == 4)) {
       addPlayer();
    }
    else if (str == "assigncountries" && getState() ==4) {
        assignCountries();
        assignReinforcementPhase();
    }
    else {
        cout << "Invalid command!" << endl;
    }

    notify(this); // FROM SUBJECT
}
*/

void GameEngine::gamePlayTransitions(string str, Player *p) {
    if (str == "issueorder" && (*getState() == 5 || *getState() == 6)) {
        issueOrdersPhase();
    }
    else if (str == "endissueorders" && *getState() == 6) {
        endIssueOrderPhase(p);
    }
    else if (str == "execorder" && *getState() == 7) {
        executeOrdersPhase();
    }
    else if (str == "endexecorders" && *getState() == 7) {
        endexecuteOrdersPhase(p);
    }
    else if (str == "win" && *getState() == 7) {
        winPhase(p);
    }
    else {
        cout << "Invalid command!" << endl;
    }

    notify(this); // FROM SUBJECT
}

void GameEngine::gameEndTransitions(string str) {
    if (str == "end" && *getState() == 8) {
        endPhase();
    }
    else if (str == "play" && *getState() == 8) {
        playAgain();
    }
    else {
        cout << "Invalid command!" << endl;
    }

    notify(this); // FROM SUBJECT
}

// Free method to determine whether an int vector contains a given int
bool doesContain(vector<int> arr, int in) {
    for (int i : arr) {
        if (i == in) {
            return true;
        }
    }

    return false;
}

// Reads (startup) commands sequentially from the console
void GameEngine::startupPhase() {
    *s = start;

    cout << "Welcome to Warzone!" << endl;

    // Creating the (possibly unused) FileCommandProcessorAdapter
    FileCommandProcessorAdapter *fcpa;

    cout << "Read commands from console or file?" << endl;

    string word1, word2;
    cin >> word1;

    // Catching wrong inputs
    while (word1 != "console" && word1 != "file") {
        cout << "Please try again!" << endl;
        cin >> word1;
    }

    // Creating a new CommandProcessor if reading from the console
    if (word1 == "console") {
        CommandProcessor *temp = new CommandProcessor;
        processor = temp;

        cout << "Please give a command: " << endl;
    }
    // Creating a new FileCommandProcessorAdapter if reading from a file
    else {
        cout << "Please provide the file name to read from:" << endl;
        cin >> word2;

        bool isValid = false;

        // Catching wrong inputs
        while (!isValid) {
            ifstream input(word2);

            if (input.is_open()) {
                isValid = true;
            } else {
                cout << "Please try again!" << endl;
                cin >> word2;
            }
        }

        fcpa = new FileCommandProcessorAdapter(word2);
        processor = fcpa;
    }

    // Connecting to and from the CommandProcessor
    processor->setEngine(this);
    setProcessor(processor);

    while (*s < 5) {
        cout << "Enter a command: " << endl;

        // Getting the next Command, and accessing it for local use
        processor->getCommand();
        Command *temp = processor->getCommands()[processor->getCommands().size() - 1];

        string effect = "";

        // Making sure the command is in fact valid
        if (processor->validate(temp)) {
            string word1 = "";
            string word2 = "";
            bool hasReachedSpace = false;

            // Splitting the input into words (if it can be split)
            for (char i : temp->getCommand()) {
                if (!hasReachedSpace) {
                    if (i == ' ') {
                        hasReachedSpace = true;
                    }
                    else {
                        word1 += i;
                    }
                }
                else {
                    if (i != '<' && i != '>') {
                        word2 += i;
                    }
                }
            }

            // Use the loadmap <filename> command to select a map from a list of map files as stored in a directory, which results in the map being loaded in the game
            if (word1 == "loadmap") {
                // TODO: do I need to check if a Map has already been loaded, and if so, delete it before I create a new one?

                MapLoader loader;
                Map *m = loader.load(word2);

                if (word2.length() > 0 && word2[0] != ' ' && word2[word2.length() - 1] != ' ' && m->isGoodMap) {
                    map = m;

                    effect = "Loaded Map: " + map->getName();
                    cout << effect << "!" << endl;

                    NumberOfTerritories = m->getTerritories().size();

                    *s = mapLoaded;
                }
                else {
                    effect = "Unable to load Map";
                    cout << effect << "!" << endl;
                    // TODO: do I need to delete m here?
                }
            }
            // Use the validatemap command to validate the map (i.e. it is a connected graph, etc – see assignment 1)
            else if (word1 == "validatemap") {
                if (map->validate()) {
                    effect = "Validated Map: " + map->getName();
                    cout << effect << "!" << endl;

                    *s = mapValidated;
                }
                else {
                    effect = "Unable to validate Map";
                    cout << effect << "!" << endl;
                }
            }
            // Use the addplayer <playername> command to enter players in the game (2-6 players)
            else if (word1 == "addplayer") {
                if (player_list.size() >= 6) {
                    effect = "Unable to add Player (6 players reached)";
                    cout << effect << "!" << endl;
                }
                else {
                    if (word2.length() > 0 && word2[0] != ' ' && word2[word2.length() - 1] != ' ') {
                        Player *p = new Player(word2);
                        player_list.push_back(p);
                        NumberOfPlayers++;

                        effect = "Added Player: " + p->getName();
                        cout << effect << "!" << endl;

                        *s = playersAdded;
                    }
                    else {
                        effect = "Unable to add Player";
                        cout << effect << "!" << endl;
                    }
                }
            }
            else if (word1 == "gamestart") {
                if (player_list.size() < 2) {
                    effect = "Unable to start game (not enough players)";
                    cout << effect << "!" << endl;
                }
                else {
                    int playerIndex = 0;

                    // Fairly distribute all the territories to the players
                    for (Territory *i : map->getTerritories()) {
                        Player *tempPlayer = player_list.at(playerIndex);
                        i->setOwner(tempPlayer);
                        tempPlayer->assignTerritory(i);

                        playerIndex++;

                        if (playerIndex >= player_list.size()) {
                            playerIndex = 0;
                        }
                    }

                    effect = "Distributed Territories to Players";

                    vector<int> tempOrder = vector<int>();

                    // Determine randomly the order of play of the players in the game
                    for (int j = 0; j < player_list.size(); j++) {
                        int randOrder = rand() % player_list.size();

                        while (doesContain(tempOrder, randOrder)) {
                            randOrder = rand() % player_list.size();
                        }

                        cout << randOrder << endl;

                        tempOrder.push_back(randOrder);
                    }

                    setPlayerOrder(tempOrder);

                    effect += ", randomly determined the order of playing order";

                    for (Player* k : player_list) {
                          // TODO: these methods below are causing errors
//                        // Give 50 initial armies to the players, which are placed in their respective reinforcement pool
//                        k->addToReinforcePool(50);
//
//                        // Let each player draw 2 initial cards from the deck using the deck’s draw() method
//                        k->getHand()->drawCard(*deck);
//                        k->getHand()->drawCard(*deck);
                    }

                    effect += ", gave 50 armies to each Player, and drew 2 cards for each Player";

                    // Switch the game to the play phase

                    *s = assignReinforcement;
                }
            }
        }

        temp->saveEffect(effect);
    }

    // TODO: ALSO ADD GameEngine Pointer to attribute to Order Class
    // Order::setGameEngine(new );

    notify(this); // FROM SUBJECT
}

// Main game loop, includes reinforcement phase, issue order phase, execute order phase
bool GameEngine::mainGameLoop() {
    bool playing = true;
    bool continueplaying;
    string input;
    while (playing == true) {
        assignReinforcementPhase(); // Begin reinforcement phase for all players
        issueOrdersPhase(); // Begin issue orders phase for all players
        executeOrdersPhase(); // Begin execute orders phase for all players
        checkPlayers(); // Check if any players need to be removed
        resetAlliances(); // Reset Alliances

        // Win phase is started in check for winner
        playing = !checkForWinner(); // Check for winner
    }

    while (*s == 8) {
        cout << "Replay or quit? " << endl;

        processor->getCommand();

        Command *temp = processor->getCommands()[processor->getCommands().size() - 1];

        string command = temp->getCommand();
        string effect = "";

        if (command == "replay") {
            playAgain();
            *s = start; // Switch to start up for replay

            effect = "Replaying game";
            cout << effect << "!" << endl;
            continueplaying = true;

        }
        else if (command == "quit") {
            endPhase();

            effect = "Quitting game";
            cout << effect << "!" << endl;
            continueplaying = false;
        }

        temp->saveEffect(effect);
    }
    return continueplaying;
}

// Check if a player has won by looping through territories and checking owner
bool GameEngine::checkForWinner() {
    int lost = 0;
    for (Player* p : player_list) {
        string player = p->getName();
        for (Territory *i : map->getTerritories()) {
            string owner = i->getOwner()->getName();
            if (owner != player) {
                lost = lost + 1;
                break;
            }
        }
        if (lost == 0) {
            winPhase(p);
            return true;
        }
    }
    cout<<"No winner, therefore continue"<<endl;
    return false;
}

// Check that players are still valid, remove players that are not
// Validity : must own at least on territory
void GameEngine::checkPlayers() {
    for (int i = 0; i <player_list.size(); i++) {
        int ordervalue = playerOrder[i];
        Player *p = player_list.at(ordervalue);
        if (p->getNumberOfTerritories() == 0) {
            cout << "Player " << p->getName() << " has been eliminated" <<endl;
            NumberOfPlayers = NumberOfPlayers - 1; // Lowers player count
            player_list.erase(player_list.begin() + playerOrder[i]); // Removes player from player_list
            for (int j = i; j <= player_list.size()-1; j++) { // Removes from playing order
                playerOrder[j] = (playerOrder[j+1]);
            }
            for (int k = 0; k < player_list.size(); k++) { // Accommodates playerOrder for change in playerlist size
                if (playerOrder[k] > ordervalue) playerOrder[k] = playerOrder[k] - 1;
            }
        }
    }
}

// Check that a card type is in a specific hand
int GameEngine::checkCardInHand(string type, Hand* h) {
    int index = 0; // Returns index of card in hand, -1 if card is not in hand
    for (Card* c : h->hand) {
        if (equalsIgnoreCase(c->getType(), type)) return index;
        index = index + 1;
    }
    return -1;
}

bool GameEngine::equalsIgnoreCase(string s1, string s2) {
   // Change to lower case
   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
   if (s1 == s2) return true;
   else return false;
}

// From Iloggable
string GameEngine::stringToLog() {
    string enumStates[] = {"null", "start", "mapLoaded", "mapValidated", "playersAdded", "assignReinforcement",
                           "issueOrder", "executeOrder", "win"};
    string logString = "Game Engine now at the " + enumStates[*s] + "state. \n";
    return logString;
}
