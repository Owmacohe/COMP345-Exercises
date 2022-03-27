#include "LoggingObserver.h"

/****************************** Iloggable *******************************/
string Iloggable::stringToLog(){return "";}

/****************************** Observer *******************************/
Observer::Observer(){}; // Constructor
Observer::~Observer(){}; // Destructor

/****************************** LogObserver *******************************/

LogObserver::LogObserver(){
    fileName = "";
    outputFile.open(fileName);}

LogObserver::LogObserver(string name){
    fileName = name;
    outputFile.open(fileName);}

LogObserver::~LogObserver(){
    outputFile.close();} // Destructor

void LogObserver::update(Iloggable* il){
    cout << "writing stringToLog to output file." << endl;
    outputFile << (*il).stringToLog() << "\n";
};

/****************************** Subject *******************************/
Subject::Subject(){}
Subject::~Subject(){};  // Destructor
LogObserver* Subject::getLogObserver(){return logObs;}
void Subject::setLogObserver(LogObserver* lo){logObs = lo;}

void Subject::notify(Iloggable* il){logObs->update(il);};

