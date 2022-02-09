#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

#include "Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include  "../Cards/Cards.h"

int Playermain() {
	// create player obj
	Hand *hand = new Hand; 
	OrdersList *orderlist = new OrdersList;
	Territory *territory1 = new Territory;
	Territory *territory2 = new Territory;
	vector<Territory*> territories (territory1, territory2);
	Player p1 = Player("Player 1", territories, hand, orderlist);
	cout << p1;

	// test issueOrder method
	cout << "results of .issueOrder()";
	p1.issueOrder();
	cout << p1;

	// test toDefend and toAttack methods
	vector<Territory*> attack = p1.toAttack();
	cout << "results of .toAttack()";
	for (Territory* i : attack) cout << i;

	vector<Territory*> defend = p1.toDefend();
	cout << "results of .toDefend()";
	for (Territory* i : defend) cout << i;

	return 0;
}