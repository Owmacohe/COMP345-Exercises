//// From notes: a cpp file should not be included as it effectively merges two compilation units together

#include "Orders.h"

<<<<<<< Updated upstream
int Ordersmain() {
	//Create OrderList object
	OrdersList player1List;
	cout << player1List;
=======
int ordersMain() {
//	Create OrderList object
    OrdersList player1List;
    cout << player1List;
>>>>>>> Stashed changes

	//Deploy
	Deploy *deploy1 = new Deploy(true, "deploy");
	cout << "Adding to the OrdersList, Order: "<< *deploy1 << endl;
	player1List.addOrder(deploy1);
	cout << player1List << endl;

	// Advance
	Advance *advance1 = new Advance( true, "advance");
	cout << "Adding to the OrdersList, Order: "<< *advance1 << endl;
	player1List.addOrder(advance1);
	cout << player1List;

	// Bomb
	Bomb *bomb1 = new Bomb(true, "bomb");
	cout << "Adding to the OrdersList, Order: "<< *bomb1 << endl;
	player1List.addOrder(bomb1);
	cout << player1List;

	// Blockade
	Blockade *blockade1 = new Blockade(true, "blockade");
	cout << "Adding to the OrdersList, Order: "<< *blockade1 << endl;
	player1List.addOrder(blockade1);
	cout << player1List;

	// Airlift
	Airlift *airlift1 = new Airlift(true, "airlift");
	cout << "Adding to the OrdersList, Order: "<< *airlift1 << endl;
	player1List.addOrder(airlift1);
	cout << player1List;

	//Negotiate
	Negotiate *negotiate1 = new Negotiate(true, "negotiate");
	cout << "Adding to the OrdersList, Order: "<< *negotiate1 << endl;
	player1List.addOrder(negotiate1);
	cout << player1List;

<<<<<<< Updated upstream

	//Create through copy constructor object
	OrdersList player1List2;
    player1List2 = OrdersList(player1List);
	cout << player1List2;

	//Create through assignment operator object
	OrdersList player1List3 = player1List;
	cout << player1List3;

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

	// Check the deep copies
	cout << "Original, now modified list" << endl;
	cout << player1List;

	cout << "Copy through the copy constructor" << endl;
	cout << player1List2;

	cout << "Copy through the assignment operator" << endl;
	cout << player1List3;
	
=======
//	//Create through copy constructor object
//	OrdersList player1List2;
//    player1List2 = OrdersList(player1List);
//	cout << player1List2;

//	//Create through assignment operator object
//	OrdersList player1List3 = player1List;
//	cout << player1List3;
//
//	//Move()
//	cout << "List before the switch" <<endl;
//	cout << player1List;
//	player1List.move(2,3);
//	cout << "List after the switch" <<endl;
//	cout << player1List;
//
//	//Remove()
//	cout << "List before the removal of order 2" <<endl;
//	cout << player1List;
//	player1List.remove(2);
//	cout << "List after the removal of order 2" <<endl;
//	cout << player1List;
//
//	//Delete orders lists and orders to free memory
//	player1List.~OrdersList();
//	cout << player1List;
//
//	// Check the deep copies
//	cout << "Original, now modified list" << endl;
//	cout << player1List;
//
//	cout << "Copy through the copy constructor" << endl;
//	cout << player1List2;
//
//	cout << "Copy through the assignment operator" << endl;
//	cout << player1List3;
//
>>>>>>> Stashed changes
	return 0;
}

