#include "Orders.h"
using namespace std;
int OrderMain() {

//Create OrderList object
OrdersList player1List = OrdersList();

//Deploy
Deploy *deploy1 = new Deploy;
cout << deploy1;
player1List.addOrder(deploy1);
cout << player1List;

// Advance
// Bomb
// Blockade
// Airlift
//Negotiate

//Move
//Remove

//Delete orders lists and orders to free memory

		return 0;
}

// int Main() {
// 	OrderMain();
// }