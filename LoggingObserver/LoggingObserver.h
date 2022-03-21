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
    Observer(); // Constructor
    ~Observer(); // Destructor
    virtual void update(Iloggable* il) = 0; // Virtual method called upon by Notify from the Subject
};

class LogObserver : public Observer{
public:
    LogObserver(); // Constructor
    LogObserver(string fileName); // Parameterized Constructor
    ~LogObserver(); // Destructor
    void update(Iloggable* il); // Method to update the concrete observer object

public:
    string fileName; // Name of file to output game logs
    ofstream outputFile; // output Stream for the game logs
};

class Subject {
public:
    Subject(); // Constructor
    ~Subject(); // Destructor
    void notify(Iloggable* il); // Method to Notify the Update method of the Observer
    void attach(Observer *obs); // Method to attach the observer to the Subject's list of subscribers
    void detach(Observer *obs); // Method to detach the observer to the Subject's list of subscribers

    public:
    list<Observer*> observers; // Not used as per model of assignment
};
