#pragma once
#include <iostream>

class Subject{
    void attach(Observer* o);
    void detach(Observer* o);
    void notify();
};

class Observer{

    ~Observer();
    virtual void update() = 0;

protected:
    Observer();
};

class Iloggable{
    string virtual stringTolog();
};

class LogObserver{};

/**
 * Subjects of logging mechanism that will have to inherit Iloggable:
 * Command
 * CommandProcessor
 * FileCommandProcessorAdapter
 * OrderList
 * Order
 * GameEngine
 *
*/