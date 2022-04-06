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
    // Set to all lowercase
    transform(type.begin(), type.end(), type.begin(), ::tolower);

    if (type == "deploy") {
        // Issues deploy orders based on toDefend()
        Deploy* d = new Deploy(p);
        p->addOrderList(d); // Add order to list
    }
    else if (type == "advance") {
        Advance* a = new Advance(p, "attack");
        p->addOrderList(a);
    }
        // Orders that involve card will be issued using playCard()
    else {
        cout << "Invalid order" << endl;
    }
}

vector<Territory*> AggressivePlayerStrategy::toAttack(Map* m) {
    vector<Territory*> attack_territories = vector<Territory*>();
    pair<int, Territory*> pairs;
    vector<pair<int, Territory*>> ordering;

    for (Territory* territory : p->getTerritoryList()) { // Looping through the player's territories
        int number_armies = 0;
        string name = territory->getName();

        // step 1 get connected territories
        vector<Territory*> surround_territory = m->getConnectedTerritories(name); // Getting surrounding territories of the player's territory

        if (surround_territory.empty()) { // If the territories do not have any surrounding or connected territories
            cout << "Surround territory vector for that territory is empty."  << endl;
        }

        // step 2 for each connected territory that's an enemy's count the number armies
        for (Territory* t : surround_territory) {
            if ((t->getOwner()->getName() != p->getName())) {
                number_armies = t->getArmies();
                // step 3 pair enemy territory and their number of armies, add pair to vector
                pairs.first = number_armies;
                pairs.second = t;
                ordering.push_back(pairs);
            }
        }

        for (Territory* i : surround_territory) { // Delete the vector of the surrounding to avoid memory leak
            i = NULL;
        }
    }

    // step 3 sort and separate territories in pair
    if(ordering.empty()) {
        cout << "No territories to Attack." << endl;
    }
    else {
        sort(ordering.begin(), ordering.end());
        ordering.erase(unique(ordering.begin(), ordering.end()), ordering.end());
        for (pair<int, Territory*> p : ordering) {
            attack_territories.insert(attack_territories.end(), p.second); // Pushes them in one by one because they are already sorted (insert at the front because it is sorted small to large)
            p.second = NULL; // Dangling pointer avoidance
        }
    }

    return attack_territories;
}

vector<Territory*> AggressivePlayerStrategy::toDefend(Map* m) {
    vector<Territory*> defend_territories = vector<Territory*>();
    pair<int, Territory*> pairs;
    vector<pair<int, Territory*>> ordering;

    for (Territory* territory : p->getTerritoryList()) { // Looping through the player's territories

        int number_surrounding = 0;
        string name = territory->getName();

        vector<Territory *> surrounded_territories = m->getConnectedTerritories(name);

        if (surrounded_territories.empty()) {
            number_surrounding = -1;
        }
        // step 1 check each territories numbers of enemies surrounding
        else {
            for (Territory *t: surrounded_territories) {
                if ((t->getOwner()->getName() != p->getName())) {
                    number_surrounding = number_surrounding + 1;
                }
            }
        }

        // step 2 pair territory and their number of surrounding territories, add pair to vector
        if (number_surrounding != 0) {
            pairs.first = territory->getArmies();
            pairs.second = territory;
            ordering.push_back(pairs);
        }

        for (Territory* i : surrounded_territories) { // Delete the vector of the surrounding to avoid memory leak
            i = NULL;
        }

        // step 3 sort and seperate territories in pair
        sort(ordering.begin(), ordering.end());

        for (pair<int, Territory*> p : ordering) {
            defend_territories.insert(defend_territories.begin(), p.second);// Pushes them in one by one because they are already sorted (insert at the front because it is highest number of armies to smallest)
            p.second = NULL; // Dangling pointer avoidance
        }

        return defend_territories;
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
// Free Function
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