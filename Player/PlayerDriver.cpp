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
	Player p2 = Player(p1);
	cout<<p2<<endl;
	p1.setName("Player Player Player");
	cout<<p1<<endl;
	cout<<p2<<endl;

	return 0;
}