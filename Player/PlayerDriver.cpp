#include "Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

#include "Player.cpp"
#include "../Map/Map.cpp"
#include "../Orders/Orders.cpp"
#include "../Cards/Cards.cpp"

int PlayerMain() {

	// cout << "\nPlayer Test Default Constructor" <<endl;
	// //test default constructor
	// Player p1;
	// cout<< p1 <<endl;

	// cout  <<"\nPlayer Test Param Constructor" <<endl;
	// //test param constructor
	// Player *p2 = new Player;
	// Deck mainDeck(10);

	// Territory *t1 = new Territory("t1", "", p2, 0);
	// Territory *t2 = new Territory("t2", "", p2, 0);
	// vector<Territory*> v{t1, t2};

	// Hand *h = new Hand;
	// cout<<"drawing cards for player: ";
	// (*h).drawCard(mainDeck);
	// (*h).drawCard(mainDeck);
	// (*h).drawCard(mainDeck);
	// cout<<endl;

	// Order o1(true, "random order");
	// Order o2(true, "random order");
	// OrdersList *o = new OrdersList();
	// (*o).addOrder(o1);
	// (*o).addOrder(o2);

	// delete p2;
	// p2 = new Player("Player Player", v, h, o);
	// cout<< *p2 <<endl;

	// cout  <<"\nPlayer Test IssueOrder()" <<endl;
	// // test issueOrder method
	// (*p2).issueOrder("bomb");
	// cout<< (*p2);

	// cout <<"\nPlayer Test toAttack()" <<endl;
	// // test toAttack method
	// vector<Territory*> attack = (*p2).toAttack();
	// cout<<"results of .toAttack(): ";
	// for (Territory* i : attack) cout<< (*i).getName() << " ";
	// cout<<endl;

	// cout <<"\nPlayer Test toDefend()" <<endl;
	// // test toDefend method
	// vector<Territory*> defend = (*p2).toDefend();
	// cout<<"results of .toDefend(): ";
	// for (Territory* i : defend) cout<< (*i).getName() << " ";
	// cout<<endl;
	
	// cout <<"\nPlayer Test Copy Constructor" <<endl;
	// //test copy constructor
	// cout<<"before changing original player"<<endl;
	// p1.setName("Player Copy");
	// cout<<p1<<endl;
	// Player p3 = Player(p1);
	// cout<<p3<<endl;
	// p1.setName("Player Copied");
	// cout<<"after changing original player"<<endl;
	// cout<<p1<<endl;
	// cout<<p3<<endl;

	 return 0;
}