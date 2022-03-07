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
    void notify(Iloggable* il);
    void attach(Observer *obs);
    void detach(Observer *obs);


    public:
    list<Observer*> observers; // Not used as per model of assignment
};
