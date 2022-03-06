#include "Orders.h"
#include "../LoggingObserver/LoggingObserver.h"

int OrdersMain() {
	//	Create OrderList object
    OrdersList player1List;
    cout << " Empty Order List: " << player1List << endl;
//    Order *order1 = new Order();
//    cout << Order::game;

    cout << "****************************** Creating Orders, validate(), execute() and inserting them *******************************" <<endl;
//	//Deploy
//	Deploy *deploy1 = new Deploy();
//	cout << "Adding to the OrdersList the Order: "<< *deploy1 << endl;
//    cout << "Checking for validation: " << deploy1->validate() << endl;
//    cout << "Checking for execution: " ; deploy1->execute() ;
//	player1List.addOrder(deploy1);
//	cout << player1List << "\n" << endl;
//
//	// Advance
//	Advance *advance1 = new Advance( );
//	cout << "Adding to the OrdersList the Order: "<< *advance1 << endl;
//    cout << "Checking for validation: " << advance1->validate() << endl;
//    cout << "Checking for execution: " ; advance1->execute() ;
//	player1List.addOrder(advance1);
//	cout << player1List << "\n" << endl;

	// Bomb
	Bomb *bomb1 = new Bomb();
	cout << "Adding to the OrdersList the Order: "<< *bomb1 << endl;
    cout << "Checking for validation: " << bomb1->validate() << endl;
    cout << "Checking for execution: " ; bomb1->execute() ;
	player1List.addOrder(bomb1);
	cout << player1List << "\n" << endl;

	// Blockade
	Blockade *blockade1 = new Blockade();
	cout << "Adding to the OrdersList the Order: "<< *blockade1 << endl;
    cout << "Checking for validation: " << blockade1->validate() << endl;
    cout << "Checking for execution: " ; blockade1->execute() ;
	player1List.addOrder(blockade1);
	cout << player1List << "\n" << endl;

//	// Airlift
//	Airlift *airlift1 = new Airlift();
//	cout << "Adding to the OrdersList the Order: "<< *airlift1 << endl;
//    cout << "Checking for validation: " << airlift1->validate() << endl;
//    cout << "Checking for execution: " ; airlift1->execute() ;
//	player1List.addOrder(airlift1);
//	cout << player1List << "\n" << endl;

	//Negotiate
	Negotiate *negotiate1 = new Negotiate();
	cout << "Adding to the OrdersList the Order: "<< *negotiate1 << endl;
    cout << "Checking for validation: " << negotiate1->validate() << endl;
    cout << "Checking for execution: " ; negotiate1->execute() ;
	player1List.addOrder(negotiate1);
	cout << player1List << "\n" << endl;
//
//    cout << "****************************** Copy constructor and assignment operator *******************************"<<endl;
//	//Create through copy constructor object
//    cout << "Creating a deep copy of the OrderList through the Copy constructor\n" <<endl;
//	OrdersList player1List2(player1List);
//
//	//Create through assignment operator object
//    cout << "Creating a deep copy of the OrderList through the assignment operator \n" <<endl;
//	OrdersList player1List3 = player1List;

//    cout << "****************************** move() *******************************" << endl;
//	//Move()
//	cout << "List before the move of Advance to the index 3" <<endl;
//	cout << player1List << "\n" <<endl;
//	player1List.move(1,3);
//	cout << "List after the move of Advance to the index 3" <<endl;
//	cout << player1List << "\n" <<endl;
//    player1List.move(3,0);
//    cout << "List after the move of Advance to index 0" <<endl;
//    cout << player1List << "\n" <<endl;
//    player1List.move(0,5);
//    cout << "List after the move of Advance to the index 5" <<endl;
//    cout << player1List << "\n" <<endl;

//    cout << "****************************** remove() *******************************" <<endl;
//	//Remove()
//	cout << "List before the removal of order #2" <<endl;
//	cout << player1List << "\n" <<endl;
//	player1List.remove(2);
//	cout << "List after the removal of order #2" <<endl;
//	cout << player1List << "\n" <<endl;

    cout <<"****************************** Verification of deep copies *******************************" <<endl;
	// Check the deep copies
	cout << "Original, now modified list" << endl;
	cout << player1List << "\n" <<endl;
//
//	cout << "Copy through the copy constructor" << endl;
//	cout << player1List2 << "\n" <<endl;
//
//	cout << "Copy through the assignment operator" << endl;
//	cout << player1List3 << "\n" <<endl;

	return 0;
}

