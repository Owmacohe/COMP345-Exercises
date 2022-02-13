#include "Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

#include "Player.cpp"
#include "../Map/Map.cpp"
#include "../Orders/Orders.cpp"
#include "../Cards/Cards.cpp"

int PlayerMain() {


	cout << "Player test!" << endl;
	//test default constructor
	Player p1;
	cout<<p1.getName()<<endl;
	cout<<p1<<endl;

	//test param constructor
	//Player p2;
	//Territory *t1 = new Territory("t1", "", p2, 0);
	//Territory *t2 = new Territory("t2", "", p2, 0);
	//vector<Territory*> v (t1, t2);
	//Hand *h = new Hand;
	//OrdersList *o = new OrdersList;
	//p2 = Player("Player Player", v, h, o);
	//cout<<p2<<endl;

	// test issueOrder method
	cout<< "results of .issueOrder()";
	p1.issueOrder();
	cout<< p1;

	// test toDefend and toAttack methods
	vector<Territory*> attack = p1.toAttack();
	cout<<"results of .toAttack()";
	for (Territory* i : attack) cout << i << " ";

	vector<Territory*> defend = p1.toDefend();
	cout<<"results of .toDefend()";
	for (Territory* i : defend) cout << i << " ";
	
	cout <<endl;
	
	//test copy constructor
	p1.setName("Player Player");
	cout<<p1<<endl;
	Player p3 = Player(p1);
	cout<<p3<<endl;
	p1.setName("Player Player Player");
	cout<<p1<<endl;
	cout<<p3<<endl;

	return 0;
}