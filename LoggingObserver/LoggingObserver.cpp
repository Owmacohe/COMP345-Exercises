#include "LoggingObserver.h"

string Iloggable::stringToLog(){
return "";
};

Subject::Subject(){
observers = list<Observer*>();}

Subject::~Subject(){
    for (Observer* i : observers) {
        delete i;
        i = NULL;
        cout << "deleting an observer in Observers of the subject" <<endl;
    }
    observers .clear();
    cout << "deleted Observers of subject" <<endl;
};

void Subject::attach(Observer *obs){
observers.push_back(obs);
};

void Subject::detach(Observer *obs){
observers.remove(obs);
};

void Subject::notify(Iloggable* il){
    for (Observer* i : observers) {
        i->update(il);
    }
};

Observer::Observer(){};
Observer::~Observer(){};


LogObserver::LogObserver(){
fileName = "";
outputFile.open(fileName);}

LogObserver::LogObserver(string name){
    fileName = name;
    outputFile.open(fileName);}

LogObserver::~LogObserver(){};

void LogObserver::update(Iloggable* il){
    outputFile << (*il).stringToLog() << "\n";
};