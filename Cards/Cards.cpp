#include "Cards.h"
#include "../Orders/Orders.h"

/*********************************** CARD ***********************************/
// Constructor Default
Card::Card(){
    type = " ";
}
// Constructor Parameterized
Card::Card(string theType){

    type = theType;
}
// Copy constructor
Card::Card(Card &anotherCard){

    type = anotherCard.type;
}

// Destructor
Card::~Card();

// Accessor
string Card::getType() const {
    return type;
}
// Play method to create an Order object to issue an Order. Remove Card from Hand and place it in the deck
void Card::play(OrdersList &playerOrdersList) const{
    //Creat Order of the corresponding type
    if (type == "bomb"){
       cout << "Play Bomb card" << endl;
        Bomb* myBomb = new Bomb(); // Create a Bomb object and play as an order
        playerOrdersList.addOrder(myBomb); // Place it in the OrdersList
    } else if (type == "reinforcement"){
       cout << "Play Reinforcement card" << endl;
        Reinforcement* myReinforcement = new Reinforcement();
        playerOrdersList.addOrder(myReinforcement);
    } else if (type == "blockade"){
       cout << "Play Blockade card" << endl;
        Blockade* myBlockade = new Blockade();
        playerOrdersList.addOrder(myBlockade);
    } else if (type == "airlift"){
       cout << "Play Airlift card" << endl;
       Airlift* myAirlift = new Airlift();
       playerOrdersList.addOrder(myAirlift);
    } else if (type == "diplomacy") {
        cout << "Play Diplomacy card" << endl;
        Diplomacy *myDiplomacy = new Diplomacy();
        playerOrdersList.addOrder(myDiplomacy);
    } else {
        cout << "Invalid card, play() can not be called!" << endl;
    }

}
// Stream insertion
ostream& operator<<(ostream& os, const Card& c)
{
    os << c.getType();
    return os;
}
// Assignment operator
Card& Card::operator=(const Card &toAssign) {
    type = toAssign.type;
    return *this;
}

/*********************************** DECK ***********************************/
// Constructor Default
Deck::Deck(){
    srand (time(NULL));
    numCardInDeck = 0;
    deck = vector<Card*>();
}
// Constructor Parameterized
Deck::Deck(int numCard) {
    srand(time(NULL));
    numCardInDeck = numCard;
    if (numCardInDeck % 5 != 0) {
        cout << "The number of cards you entered is not divisible by 5. "
                "A default deck of 50 cards will be used instead." << endl;
        numCardInDeck = 50;
    }

    deck = vector<Card*>();

    for (int i = 0; i < numCardInDeck; i++) {
        if (i % 5 == 0) {
            deck.push_back(new Card("bomb"));
        } else if (i % 5 == 1) {
            deck.push_back(new Card("reinforcement"));
        } else if (i % 5 == 2) {
            deck.push_back(new Card("blockade"));
        } else if (i % 5 == 3) {
            deck.push_back(new Card("airlift"));
        } else {
            deck.push_back(new Card("diplomacy"));
        }
    }
}
// Copy constructor
Deck::Deck(Deck &anotherDeck) {
    srand(time(NULL));
    numCardInDeck = anotherDeck.numCardInDeck;

    deck = vector<Card*>();
    for ( int i=0; i<anotherDeck.numCardInDeck; i++){
        Card* cards = new Card(*anotherDeck.deck.at(i));
        deck.push_back(cards);
    }
}

// Destructor
Deck::~Deck(){
    for (int i=0; i<deck.size();i++){
        delete deck.at(i);
        deck.at(i) = NULL;
    }
    deck.clear();
}

// Draw method removes card from deck and returns the card selected
Card* Deck::draw(){
    // Generate a random number
    int numRandom = rand() % numCardInDeck;

    // keep a copy of the returned card in a temp var
    Card * temp = deck.at(numRandom);

    //Display the type of card that is drawn
    cout << numRandom << "-" << *deck.at(numRandom) << " | ";

    // Remove the drawn card from Deck
    deck.erase(deck.begin()+numRandom);
    numCardInDeck--;
    return temp;
}

//insertion operator
ostream& operator<<(ostream& os, const Deck& d){
    os << "Number of card in deck: " << d.numCardInDeck << endl;
    for(int i = 0; i < d.numCardInDeck; i++){
        os << *(d.deck.at(i)) << " | ";
    }
    return os;
}
// Assignment operator
Deck& Deck::operator=(const Deck& toAssign){
    numCardInDeck = toAssign.numCardInDeck;
    deck = toAssign.deck;
    return *this;
}

/*********************************** HAND ***********************************/
// Constructor Default
Hand::Hand(){
    numCardInHand = 0;
    hand = vector<Card*>();
}
// Copy Constructor
Hand::Hand(Hand &anotherHand){
    numCardInHand = anotherHand.numCardInHand;

    hand = vector<Card*>();
    for (int i=0; i<anotherHand.numCardInHand; i++){
        Card* cards = new Card(*anotherHand.hand.at(i));
        hand.push_back(cards);
    }
}
// Destructor
Hand::~Hand(){
    for (int i=0;i<hand.size();i++){
        delete hand.at(i);
        hand.at(i) = NULL;
    }
    hand.clear();
}
// Stream insertion
ostream& operator<<(ostream& os, const Hand& h)
{
    os << "Number of cards on hand: " << h.numCardInHand << endl;
    for(int i = 0; i < h.numCardInHand; i++){
        os << i << "-" << *(h.hand.at(i)) << " | ";
    }
    return os;
}
//Assignment operator
Hand& Hand::operator=(const Hand& toAssign){
    numCardInHand = toAssign.numCardInHand;
    hand = toAssign.hand;
    return *this;
}
// Method to insert a card into the Hand
void Hand::drawCard(Deck& d){
    Card* drawnCard = d.draw();
    // Put the drawn card into Player hand
    hand.push_back(drawnCard);
    numCardInHand++;
}

// Method to add a card into the deck and remove it frm the Hand
void Hand::playCard(int i, Deck &d, OrdersList &l) {
    // Create Order and add Order to OrderList
    hand.at(i)->play(l);

    // Add the played Card back to deck
    Card* playedCard =hand.at(i);
    d.deck.push_back(playedCard);
    d.numCardInDeck++;

    // Remove card from Hand
    hand.erase(hand.begin()+i); // Delete the card object along with its pointer
    numCardInHand--;
}
