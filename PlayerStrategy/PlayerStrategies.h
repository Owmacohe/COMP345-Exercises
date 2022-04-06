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

bool equalsIgnoreCase(string, string);

class PlayerStrategies {
    public:
        /*
         * Default constructor
         */
        PlayerStrategies();

        // Copy constructor
        PlayerStrategies(const PlayerStrategies& other);

        virtual void issueOrder(string type) = 0;
        virtual vector<Territory*> toAttack(Map* m) = 0;
        virtual vector<Territory*> toDefend(Map* m) = 0;

        // Assignment Operator Overload
        const PlayerStrategies& operator= (const PlayerStrategies &ps);

        // Stream insertion operator Overload
        friend std::ostream& operator<< (std::ostream& os, const PlayerStrategies& ps);

    private:
        Player* p;
};

class HumanPlayerStrategy : PlayerStrategies{
    public:
        // Default constructor
        HumanPlayerStrategy();

        // Copy constructor
        HumanPlayerStrategy(const HumanPlayerStrategy& other);

        void issueOrder(string type) override;
        vector<Territory*> toAttack(Map* m) override;
        vector<Territory*> toDefend(Map* m) override;

        //Assignment Operator Overload
        const HumanPlayerStrategy& operator= (const HumanPlayerStrategy& humanPs);

        //Stream insertion operator Overload
        friend std::ostream& operator<< (std::ostream& os, const HumanPlayerStrategy& humanPs);

    private:
        Player* p;
};

class AggressivePlayerStrategy : PlayerStrategies{
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

class BenevolentPlayerStrategy : PlayerStrategies{
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

class NeutralPlayerStrategy  : PlayerStrategies{
    public:
        // Default constructor
        NeutralPlayerStrategy();

        // Copy constructor
        NeutralPlayerStrategy(const NeutralPlayerStrategy& other);

        void issueOrder(string type) override;
        std::vector<Territory*> toAttack(Map* m) override;
        std::vector<Territory*> toDefend(Map* m) override;

        //Assignment Operator Overload
        const NeutralPlayerStrategy& operator= (const NeutralPlayerStrategy& neutralPs);

        //Stream Insertion Operator Overload
        friend std::ostream& operator<< (std::ostream& os, const NeutralPlayerStrategy& neutralPs);

    private:
        Player* p;
};

class CheaterPlayerStrategy : PlayerStrategies{
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

