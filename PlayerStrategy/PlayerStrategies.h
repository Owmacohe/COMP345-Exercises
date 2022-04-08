#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Player;
class Territory;
class Order;
class Map;
class Hand;
class GameEngine;

bool equalsIgnoreCase(string, string);
int checkCardInHand(string, Hand*);

class PlayerStrategies {
        friend Player;
        friend GameEngine;
    public:

        // Default constructor
        PlayerStrategies();
        PlayerStrategies(string type);

        // Copy constructor
        PlayerStrategies(const PlayerStrategies& other);

        // Accessor
        virtual Player *getPlayer();
        string getType();

        // Mutator
        virtual void setPlayer(Player*);

        virtual void issueOrder(string type) = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual vector<Territory*> toDefend() = 0;

        // Operator overloading
        const PlayerStrategies& operator= (const PlayerStrategies &ps);
        friend std::ostream& operator<< (std::ostream& os, const PlayerStrategies& ps);

        // A static game Engine to get Map and Deck
        static GameEngine* game;

        private:
            Player* p;
            string type;
};

class HumanPlayerStrategy : public PlayerStrategies{
    public:
        // Default constructor
        HumanPlayerStrategy();

        // Copy constructor
        HumanPlayerStrategy(const HumanPlayerStrategy& other);

        void issueOrder(string type) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;

        //Assignment Operator Overload
        const HumanPlayerStrategy& operator= (const HumanPlayerStrategy& humanPs);

        //Stream insertion operator Overload
        friend std::ostream& operator<< (std::ostream& os, const HumanPlayerStrategy& humanPs);

    private:
        Player* p;
};

class AggressivePlayerStrategy : public PlayerStrategies{
    public:
        // Default constructor
        AggressivePlayerStrategy();

        // Copy constructor
        AggressivePlayerStrategy(const AggressivePlayerStrategy& other);

        void issueOrder(string type) override;
        std::vector<Territory*> toAttack() override;
        std::vector<Territory*> toDefend() override;

        //Assignment Operator Overload
        const AggressivePlayerStrategy& operator= (const AggressivePlayerStrategy& aggressivePs);

        //Stream Insertion Operator Overload
        friend std::ostream& operator<< (std::ostream& os, const AggressivePlayerStrategy& aggressivePs);

    private:
        Player* p;
};

class BenevolentPlayerStrategy : public PlayerStrategies{
    public:
        // Default constructor
        BenevolentPlayerStrategy();

        // Copy constructor
        BenevolentPlayerStrategy(const BenevolentPlayerStrategy& other);

        void issueOrder(string type) override;
        std::vector<Territory*> toAttack() override;
        std::vector<Territory*> toDefend() override;

        //Assignment Operator Overload
        const BenevolentPlayerStrategy& operator= (const BenevolentPlayerStrategy& benevolentPs);

        //Stream Insertion Operator Overload
        friend std::ostream& operator<< (std::ostream& os, const BenevolentPlayerStrategy& benevolentPs);

    private:
        Player* p;
};

class NeutralPlayerStrategy  : public PlayerStrategies{
    public:
        // Default constructor
        NeutralPlayerStrategy();

        // Copy constructor
        NeutralPlayerStrategy(const NeutralPlayerStrategy& other);

        void issueOrder(string type) override;
        std::vector<Territory*> toAttack() override;
        std::vector<Territory*> toDefend() override;

        //Assignment Operator Overload
        const NeutralPlayerStrategy& operator= (const NeutralPlayerStrategy& neutralPs);

        //Stream Insertion Operator Overload
        friend std::ostream& operator<< (std::ostream& os, const NeutralPlayerStrategy& neutralPs);

    private:
         Player* p;
};

class CheaterPlayerStrategy : public PlayerStrategies{
    public:
        // Default constructor
        CheaterPlayerStrategy();

        // Copy constructor
        CheaterPlayerStrategy(const CheaterPlayerStrategy& other);

        void issueOrder(string type) override;
        std::vector<Territory*> toAttack() override;
        std::vector<Territory*> toDefend() override;

        //Assignment Operator Overload
        const CheaterPlayerStrategy& operator= (const CheaterPlayerStrategy& cheaterPs);

        //Stream Insertion Operator Overload
        friend std::ostream& operator<< (std::ostream& os, const CheaterPlayerStrategy& cheaterPs);

    private:
        Player* p;
};