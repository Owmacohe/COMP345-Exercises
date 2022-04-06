#include "PlayerStrategies.h"

Player *PlayerStrategies::getPlayer() { return p; }

/****************************** Human Player Strategy*******************************/
/* requires user interactions to make decisions
 */

void HumanPlayerStrategy::issueOrder() {

}

vector<Territory*> HumanPlayerStrategy::toAttack() {

}

vector<Territory*> HumanPlayerStrategy::toDefend() {

}

/****************************** Aggressive Player Strategy*******************************/
/* computer player that focuses on attack
 * deploys or advances armies on its strongest country
 * always advances to enemy territories until it cannot do so anymore
 */

void AggressivePlayerStrategy::issueOrder() {

}

vector<Territory*> AggressivePlayerStrategy::toAttack() {

}

vector<Territory*> AggressivePlayerStrategy::toDefend() {

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
/* computer player that never issues any order
 * If a Neutral player is attacked, it becomes an Aggressive player
 */
void NeutralPlayerStrategy::issueOrder() {

}

vector<Territory*> NeutralPlayerStrategy::toAttack() {

}

vector<Territory*> NeutralPlayerStrategy::toDefend() {

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