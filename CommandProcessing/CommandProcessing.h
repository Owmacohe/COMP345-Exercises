#pragma once

#include <string>
#include <iostream>
#include "LoggingObserver/LoggingObserver.h"
using namespace std;


class GameEngine;

class Command : public Iloggable, public Subject {

    public:
        Command(); // Default constructor
        Command(string); // Parameterized constructor 1
        Command(string, string); // Parameterized constructor 2
        ~Command(); // Destructor

        // Accessors
        string getCommand(), *getValidIn(), getTransitionsTo(), getEffect();

        // Mutators
        void setCommand(string), setValidIn(string*, int), setTransitionsTo(string), setEffect(string);

        void addValidInState(string);

        int validInLength;

        // From Iloggable
        string stringToLog();

    private:
        string command, *validIn, transitionsTo, effect; // Command name, which states it valid in, next state, and dynamic effect of the command

};

class CommandProcessor : public Iloggable, public Subject {
    public:
        CommandProcessor(); // Default constructor
        CommandProcessor(GameEngine); // Parameterized constructor
        ~CommandProcessor(); // Destructor

        // Accessors
        Command *getCommands();
        GameEngine *getEngine();

        // Mutators
        void setCommands(Command*, int), setEngine(GameEngine*);

        Command readCommand(); // Gets command from console
        void saveCommand(const Command &c); // Stores the gotten Command in the array
        void getCommand(); // Reads and then saves a command from the console
        void saveEffect(string); // Stores the result of the current Command in the current (last) Command

        bool validate(); // Checks if the current Command is in the valid state

        int commandsLength;

        // From Iloggable
        string stringToLog();

    private:
        GameEngine *engine; // GameEngine on which the CommandProcessor is dependant for states
        Command *commands; // Array of current and past Commands
};

class FileCommandProcessorAdapter : public Iloggable, public Subject {
    public:
        void readFromFile(); // Reads commands sequentially from a file
        // From Iloggable
        string stringToLog();
};