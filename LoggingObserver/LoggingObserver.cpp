
#include "LoggingObserver.h"

    string Iloggable::stringToLog(){
    // Nothing happens here, must override
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

    /**
    * Subjects of logging mechanism that will have to inherit interfaces Iloggable and Subject:
    * Command
    * CommandProcessor
    * FileCommandProcessorAdapter
    * OrderList -- DONE .h and .cpp
    * Order  -- DONE .h and .cpp
    * GameEngine
    *
    */

    /**
     * In Each Subject
     * Add in Class Declaration of each Subject ----------------------------------------
     *  : public Iloggable, public Subject
     *
     *  Add in h file of each Subject ----------------------------------------
     *  string stringToLog();
     *
     *  Add in ccp file of each Subject ----------------------------------------
     *  string Class::stringToLog(){
     *  string logString = "STRING FORMED FROM ATTRIBUTES OR STATE OF SUBJECT FOR IT TO BE THE RETURN STRING OF THIS METHOD";
     *  return logString;}
     *
     *  add
     *  Notify(This); in each triggering method
     */