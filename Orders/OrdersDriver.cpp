#include "Orders.h"
using namespace std;
int OrderMain() {

//Create OrderList object
OrdersList player1List = OrdersList();

//Deploy
Deploy *deploy1 = new Deploy;
cout << "Adding to the OrdersList, Order: "<< deploy1;
player1List.addOrder(deploy1);
cout << player1List;

// Advance
Deploy *advance1 = new Deploy;
cout << "Adding to the OrdersList, Order: "<< advance1;
player1List.addOrder(advance1);
cout << player1List;

// Bomb
Deploy *bomb1 = new Deploy;
cout << "Adding to the OrdersList, Order: "<< bomb1;
player1List.addOrder(bomb1);
cout << player1List;

// Blockade
Deploy *blockade1 = new Deploy;
cout << "Adding to the OrdersList, Order: "<< blockade1;
player1List.addOrder(blockade1);
cout << player1List;

// Airlift
Deploy *airlift1 = new Deploy;
cout << "Adding to the OrdersList, Order: "<< airlift1;
player1List.addOrder(airlift1);
cout << player1List;

//Negotiate
Deploy *negotiate1 = new Deploy;
cout << "Adding to the OrdersList, Order: "<< negotiate1;
player1List.addOrder(negotiate1);
cout << player1List;

//Move()
cout << "List before the switch" <<endl;
cout << player1List;
player1List.move(2,3);
cout << "List after the switch" <<endl;
cout << player1List;

//Remove()
cout << "List before the removal of order 2" <<endl;
cout << player1List;
player1List.remove(2);
cout << "List after the removal of order 2" <<endl;
cout << player1List;

//Delete orders lists and orders to free memory
player1List.~OrdersList();
cout << player1List;

		return 0;
}

int Main() {
	OrderMain();
}