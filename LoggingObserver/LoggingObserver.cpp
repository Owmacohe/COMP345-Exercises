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

// Copy Constructor
LogObserver::LogObserver(const LogObserver& lo){
    fileName = lo.fileName;
}

LogObserver::~LogObserver(){
    outputFile.close();} // Destructor

// Assignment operator
LogObserver &LogObserver::operator = (const LogObserver& lo){
    fileName = lo.fileName;
    return *this;
}

// Stream insertion operator
ostream &operator<<(ostream& os, const LogObserver& logObs){
    os << "LoggingObserver is outputting in file "  << logObs.fileName << endl;
    return os;
}

void LogObserver::update(Iloggable* il){
    outputFile << (*il).stringToLog() << "\n";
};

/****************************** Subject *******************************/
Subject::Subject(){}
// Copy Constructor
Subject::Subject(const Subject& s){
    logObs = s.logObs;
}

Subject::~Subject(){};  // Destructor

// Assignment operator
Subject &Subject::operator = (const Subject& s){
    logObs = s.logObs;
    return *this;
}

LogObserver* Subject::getLogObserver(){return logObs;}
void Subject::setLogObserver(LogObserver* lo){logObs = lo;}

void Subject::notify(Iloggable* il){logObs->update(il);};

