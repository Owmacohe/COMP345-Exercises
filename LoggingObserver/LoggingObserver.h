#pragma once
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class Iloggable{
public:
    string virtual stringToLog()=0;
};

class Observer{
public:
    Observer();
    ~Observer();
    virtual void update(Iloggable* il) = 0;
};

class LogObserver : public Observer{
public:
    string fileName;
    ofstream outputFile;

    LogObserver();
    LogObserver(string fileName);
    ~LogObserver();
    void update(Iloggable* il);
};

class Subject {
public:
    Subject();
    ~Subject();

    void attach(Observer *obs);
    void detach(Observer *obs);
    void notify(Iloggable* il);

    public:
    list<Observer*> observers;
    // Does not use collection? Nope...will pass(this) in update method to do a many to one rather than one to many relationship between Subject and Observer
    // Will still implement it just ot have it and I will ask TA if necessary
};
