#pragma once
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

/****************************** Iloggable *******************************/
// Class inherited with a single method to be overriden in respective subclasses
class Iloggable{
    public:
        string virtual stringToLog()=0;
};

/****************************** Observer *******************************/
// Abstract Class
class Observer{
    public:
        Observer(); // Constructor
        ~Observer(); // Destructor
        virtual void update(Iloggable* il) = 0;}; // Virtual method called upon by Notify from the Subject

/****************************** LogObserver *******************************/
// Concrete Class to log into an output file
class LogObserver : public Observer{
    public:
        LogObserver(); // Constructor
        LogObserver(string fileName); // Parameterized Constructor
        LogObserver(const LogObserver& logObs); // Copy Constructor
        ~LogObserver(); // Destructor

    LogObserver& operator = (const LogObserver& D); // Assignment operator
    friend ostream& operator<<(ostream& os, const LogObserver& logObs); // Stream insertion operator

        void update(Iloggable* il); // Method to update the concrete observer object
    public:
        string fileName; // Name of file to output game logs
        ofstream outputFile; // output Stream for the game logs
};

/****************************** Subject *******************************/
class Subject {
public:
    Subject(); // Constructor
    Subject(const Subject&); // Copy Constructor
    ~Subject(); // Destructor
    Subject& operator = (const Subject& s); // Assignment operator

    LogObserver* getLogObserver();
    static void setLogObserver(LogObserver* logobs);

    void notify(Iloggable* il); // Method to Notify the Update method of the Observer
public:
    static LogObserver* logObs;
};
