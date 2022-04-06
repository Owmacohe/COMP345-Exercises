#pragma once

#include <vector>
#include <iostream>
#include <vector>

using namespace std;

class Player;
class Territory;

class PlayerStrategies {
    public:
        // Default constructor
        PlayerStrategies();

        // Copy constructor
        PlayerStrategies(const PlayerStrategies& other);

        // Accessor
        virtual Player *getPlayer();

        virtual void issueOrder() = 0;
        virtual std::vector<Territory*> toAttack() = 0;
        virtual std::vector<Territory*> toDefend() = 0;

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

    void issueOrder() override;
    std::vector<Territory*>toAttack() override;
    std::vector<Territory*> toDefend() override;

    //Assignment Operator Overload
    const HumanPlayerStrategy& operator= (const HumanPlayerStrategy& humanPs);

    //Stream insertion operator Overload
    friend std::ostream& operator<< (std::ostream& os, const HumanPlayerStrategy& humanPs);
};

class AggressivePlayerStrategy : PlayerStrategies{
public:
    // Default constructor
    AggressivePlayerStrategy();

    // Copy constructor
    AggressivePlayerStrategy(const AggressivePlayerStrategy& other);

    void issueOrder() override;
    std::vector<Territory*> toAttack() override;
    std::vector<Territory*> toDefend() override;

    //Assignment Operator Overload
    const AggressivePlayerStrategy& operator= (const AggressivePlayerStrategy& aggressivePs);

    //Stream Insertion Operator Overload
    friend std::ostream& operator<< (std::ostream& os, const AggressivePlayerStrategy& aggressivePs);
};

class BenevolentPlayerStrategy : PlayerStrategies{
public:
    // Default constructor
    BenevolentPlayerStrategy();

    // Copy constructor
    BenevolentPlayerStrategy(const BenevolentPlayerStrategy& other);

    void issueOrder() override;
    std::vector<Territory*> toAttack() override;
    std::vector<Territory*> toDefend() override;

    //Assignment Operator Overload
    const BenevolentPlayerStrategy& operator= (const BenevolentPlayerStrategy& benevolentPs);

    //Stream Insertion Operator Overload
    friend std::ostream& operator<< (std::ostream& os, const BenevolentPlayerStrategy& benevolentPs);
};

class NeutralPlayerStrategy  : PlayerStrategies{
public:
    // Default constructor
    NeutralPlayerStrategy();

    // Copy constructor
    NeutralPlayerStrategy(const NeutralPlayerStrategy& other);

    void issueOrder() override;
    std::vector<Territory*> toAttack() override;
    std::vector<Territory*> toDefend() override;

    //Assignment Operator Overload
    const NeutralPlayerStrategy& operator= (const NeutralPlayerStrategy& neutralPs);

    //Stream Insertion Operator Overload
    friend std::ostream& operator<< (std::ostream& os, const NeutralPlayerStrategy& neutralPs);
};

class CheaterPlayerStrategy : PlayerStrategies{
public:
    // Default constructor
    CheaterPlayerStrategy();

    // Copy constructor
    CheaterPlayerStrategy(const CheaterPlayerStrategy& other);

    void issueOrder() override;
    std::vector<Territory*> toAttack() override;
    std::vector<Territory*> toDefend() override;

    //Assignment Operator Overload
    const CheaterPlayerStrategy& operator= (const CheaterPlayerStrategy& cheaterPs);

    //Stream Insertion Operator Overload
    friend std::ostream& operator<< (std::ostream& os, const CheaterPlayerStrategy& cheaterPs);
};

