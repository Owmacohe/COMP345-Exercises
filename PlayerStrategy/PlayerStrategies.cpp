#include "PlayerStrategies.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"
#include "../Map/Map.h"

Player *PlayerStrategies::getPlayer() { return p; }

/****************************** Human Player Strategy*******************************/
/*
 * Requires user interaction :
 * User chooses whether advance is to move or to attack
 * User chooses which territory is returned from their toAttack() method
 * User chooses which territory is returned from their toDefend() method
 */

void HumanPlayerStrategy::issueOrder(string type) {
    // Set to all lowercase
    transform(type.begin(), type.end(), type.begin(), ::tolower);
    string input;

    if (type == "deploy") {
        // Issues deploy orders based on toDefend()
        Deploy* d = new Deploy(p);
        p->addOrderList(d);// Add order to list
    }
    else if (type == "advance") {
        cout << "\nWhat type of advance would " << p->getName() << " Player like to issue ? (move, attack, none)" << endl;
        cin >> input;
        while (!equalsIgnoreCase("move", input) || !equalsIgnoreCase("attack", input) || !equalsIgnoreCase("none", input)) {
            cout << "\nInvalid input ! Try Again." << endl;
            cin >> input;
        }
        if (!equalsIgnoreCase("none", input)) {
            Advance* a = new Advance(p, input);
            p->addOrderList(a);
        }
    }
        // Orders that involve card will be issued using playCard()
    else {
        cout << "Invalid order" << endl;
    }
}

vector<Territory*> HumanPlayerStrategy::toAttack(Map* m) {
    vector<Territory*> returnTerritories;
    string input;

    cout << "\nWhat territory would" << p->getName() << " Player like to attack from ?" << endl;
    cin >> input;

    while (p->checkTerritoryOwn(input) == NULL) {
        cout << "\nInvalid input " << p->getName() << "Player does not own territory ! Try Again." << endl;
        cin >> input;
    }

    Territory* territory = p->checkTerritoryOwn(input);
    vector<Territory*> territories = m->getConnectedTerritories(territory->getName());

    cout << "\nChosen territory : " << input <<". What territory would" << p->getName() << " Player like to attack ?" << endl;
    cin >> input;
    bool flag = false;
    while (flag == false) {
        for (Territory* t : territories) {
            if (equalsIgnoreCase(t->getName(), input) && (t->getOwner()->getName() != p->getName())) {
                returnTerritories.push_back(t);
                flag = true;
                break;
            }
        }
        if (flag == false) {
            cout << "\nInvalid input ! Try Again." << endl;
            cin >> input;
        }
    }
    return returnTerritories;
}

vector<Territory*> HumanPlayerStrategy::toDefend(Map* m) {
    vector<Territory*> returnTerritories;
    string input;

    cout << "\nWhat territory would" << p->getName() << " Player like to defend ?" << endl;
    cin >> input;

    while (p->checkTerritoryOwn(input) == NULL) {
        cout << "\nInvalid input " << p->getName() << "Player does not own territory ! Try Again." << endl;
        cin >> input;
    }

    vector<Territory*> territories = p->getTerritoryList();
    for (Territory* t : territories) {
        if (equalsIgnoreCase(t->getName(), input)) {
            returnTerritories.push_back(t);
            break;
        }
    }
    return returnTerritories;
}

/****************************** Aggressive Player Strategy*******************************/
/* computer player that focuses on attack
 * deploys or advances armies on its strongest country
 * always advances to enemy territories until it cannot do so anymore
 */

void AggressivePlayerStrategy::issueOrder(string type) {

}

vector<Territory*> AggressivePlayerStrategy::toAttack() {

}

vector<Territory*> AggressivePlayerStrategy::toDefend() {
    // Aggressive player has no use for toDefend()
}

/****************************** Benevolent Player Strategy*******************************/
/* computer player that focuses on protecting its weak countries
 * deploys or advances armies on its weakest countries
 * never advances to enemy territories
 */

void BenevolentPlayerStrategy::issueOrder() {

}

vector<Territory*> BenevolentPlayerStrategy::toAttack() {

}

vector<Territory*> BenevolentPlayerStrategy::toDefend() {

}

/****************************** Neutral Player Strategy*******************************/
/*
 * Player never issues any orders
 * If a Neutral player is attacked, it becomes an Aggressive player
 */
void NeutralPlayerStrategy::issueOrder(string type) {
    // Neutral player never issues orders, and therefore issueOrder() remains empty
}

vector<Territory*> NeutralPlayerStrategy::toAttack(Map* m) {
    // Neutral player doesn't issue orders, and therefore has no use for a toAttack()
}

vector<Territory*> NeutralPlayerStrategy::toDefend(Map* m) {
    // Neutral player doesn't issue orders, and therefore has no use for a toDefend()
}

/****************************** Cheater Player Strategy*******************************/
/* computer player that automatically conquers all territories that are adjacent to its own territories
 * only once per turn
 */
void CheaterPlayerStrategy::issueOrder() {

}

vector<Territory*> CheaterPlayerStrategy::toAttack() {

}

vector<Territory*> CheaterPlayerStrategy::toDefend() {

}

// Checks for returns true for strings that are equal ignoring case
bool equalsIgnoreCase(string s1, string s2) {
    // Change to lower case
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

    if (s1 == s2) {
        return true;
    }
    else {
        return false;
    }
}