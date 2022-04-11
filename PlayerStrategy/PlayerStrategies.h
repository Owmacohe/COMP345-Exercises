#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/// Forward declaration of Player
class Player;
/// Forward declaration of Territory
class Territory;
/// Forward declaration of Order
class Order;
/// Forward declaration of Map
class Map;
/// Forward declaration of Hand
class Hand;
/// Forward declaration of GameEngine
class GameEngine;

/**
 Free method to compare strings while ignoring case
 @param string to be compared
 @param string to be compared
 @return Boolean, true if string are equal and false if they are not
 */
bool equalsIgnoreCase(string, string);
/**
 Free method to check if a specific card is in a player hand
 @param string representing the card type (bomb, negotiate, airlift ..etc)
 @param Hand pointer pointing to the hand we are checking
 @return int, index of the card in hand (or -1 if card not in hand)
 */
int checkCardInHand(string, Hand*);

/**
 Class representing the abstract class for different strategy types
 */
class PlayerStrategies {
    ///PlayerStrategies is friend of Player
    friend Player;

    ///PlayerStrategies is friend of GameEngine
    friend GameEngine;

    public:

        /// Default constructor
        PlayerStrategies();

        /**
         * Parameterized constructor that creates new player based on parameters
         * @param string type of player strategy (Human, Aggressive, Benevolent, Cheater, Neutral)
         */
        PlayerStrategies(string type);

        /**
         * Parameterized constructor that creates new player based on parameters
         * @param string type of player strategy (Human, Aggressive, Benevolent, Cheater, Neutral)
         * @param Player pointer pointing to the player the strategy object belongs too
         */
        PlayerStrategies(Player*, string);

        /**
        Copy constructor that creates a deep copy
        @param constant PlayerStrategies reference
        @return pointer to the PlayerStrategies created
        */
        PlayerStrategies(const PlayerStrategies& other);

        /**
         * Virtual Accessor method for Player
         * @return Player pointer
         */
        virtual Player* getPlayer();

        /**
         * Accessor method for strategy type
         * @return string type
         */
        string getType();

        /**
         * Accessor method for boolean flag for neutral player attack
         * @return boolean if a neutral player was attacked
         */
        bool getNeutralAttack();

        /**
         * VirtualMutator method for setting player
         * @param Player pointer
         */
        virtual void setPlayer(Player*);

        /**
         * Virtual Mutator method for setting neutral attack boolean
         * @param boolean
         */
        virtual void setNeutralAttack(bool);

        /**
         * Virtual Method to issue orders into the player orderlist
         * @param string input type of order (deploy, advance or a card)type
         */
        virtual void issueOrder(string type) = 0;

        /**
         * Virtual Method to determine which territories the player should attack in priority
         * @return vector of Territory pointers player should attack
         */
        virtual vector<Territory*> toAttack() = 0;

        /**
         * Method to determine which territories the player should defend in priority
         * @return vector of Territory pointers player should defend
         */
        virtual vector<Territory*> toDefend() = 0;

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param PlayerStrategies reference that will be copied and assigned
        @return PlayerStrategies reference
        */
        const PlayerStrategies& operator= (const PlayerStrategies &ps);

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the player as a constant reference
        @return output stream reference
        */
        friend std::ostream& operator<< (std::ostream& os, const PlayerStrategies& ps);

        /// A static game Engine to access Map and Deck related
        static GameEngine* game;

    protected:
        /// Boolean to check if a neutral player has been attacked
        bool neutralAttack;

        /// Player related to strategy object
        Player* p;

        /// Strategy type (Human, Aggressive, Benevolent, Cheater, Neutral)
        string type;
};

class HumanPlayerStrategy : public PlayerStrategies{
    public:
        // Default constructor
        HumanPlayerStrategy();

        // Parameterized constructor
        HumanPlayerStrategy(Player*);

        // Copy constructor
        HumanPlayerStrategy(const HumanPlayerStrategy& other);

        void issueOrder(string type) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;

        //Assignment Operator Overload
        const HumanPlayerStrategy& operator= (const HumanPlayerStrategy& humanPs);

        //Stream insertion operator Overload
        friend std::ostream& operator<< (std::ostream& os, const HumanPlayerStrategy& humanPs);
};

class AggressivePlayerStrategy : public PlayerStrategies{
    public:
        // Default constructor
        AggressivePlayerStrategy();

        // Parameterized constructor
        AggressivePlayerStrategy(Player*);

        // Copy constructor
        AggressivePlayerStrategy(const AggressivePlayerStrategy& other);

        void issueOrder(string type) override;
        std::vector<Territory*> toAttack() override;
        std::vector<Territory*> toDefend() override;

        //Assignment Operator Overload
        const AggressivePlayerStrategy& operator= (const AggressivePlayerStrategy& aggressivePs);

        //Stream Insertion Operator Overload
        friend std::ostream& operator<< (std::ostream& os, const AggressivePlayerStrategy& aggressivePs);
};

class BenevolentPlayerStrategy : public PlayerStrategies{
    public:
        // Default constructor
        BenevolentPlayerStrategy();

        // Parameterized constructor
        BenevolentPlayerStrategy(Player*);

        // Copy constructor
        BenevolentPlayerStrategy(const BenevolentPlayerStrategy& other);

        void issueOrder(string type) override;
        std::vector<Territory*> toAttack() override;
        std::vector<Territory*> toDefend() override;

        //Assignment Operator Overload
        const BenevolentPlayerStrategy& operator= (const BenevolentPlayerStrategy& benevolentPs);

        //Stream Insertion Operator Overload
        friend std::ostream& operator<< (std::ostream& os, const BenevolentPlayerStrategy& benevolentPs);
};

class NeutralPlayerStrategy  : public PlayerStrategies{
    public:
        // Default constructor
        NeutralPlayerStrategy();

        // Parameterized constructor
        NeutralPlayerStrategy(Player*);

        // Copy constructor
        NeutralPlayerStrategy(const NeutralPlayerStrategy& other);

        void issueOrder(string type) override;
        std::vector<Territory*> toAttack() override;
        std::vector<Territory*> toDefend() override;

        //Assignment Operator Overload
        const NeutralPlayerStrategy& operator= (const NeutralPlayerStrategy& neutralPs);

        //Stream Insertion Operator Overload
        friend std::ostream& operator<< (std::ostream& os, const NeutralPlayerStrategy& neutralPs);
};

class CheaterPlayerStrategy : public PlayerStrategies{
    public:
        // Default constructor
        CheaterPlayerStrategy();

        // Parameterized constructor
        CheaterPlayerStrategy(Player*);

        // Copy constructor
        CheaterPlayerStrategy(const CheaterPlayerStrategy& other);

        void issueOrder(string type) override;
        std::vector<Territory*> toAttack() override;
        std::vector<Territory*> toDefend() override;

        //Assignment Operator Overload
        const CheaterPlayerStrategy& operator= (const CheaterPlayerStrategy& cheaterPs);

        //Stream Insertion Operator Overload
        friend std::ostream& operator<< (std::ostream& os, const CheaterPlayerStrategy& cheaterPs);
};