#pragma once

#include <string>
#include <iostream>
using namespace std;

#include "../LoggingObserver/LoggingObserver.h"

class GameEngine;

class Command : public Iloggable, public Subject {
    public:
        Command(); // Default constructor
        Command(string); // Parameterized constructor 1
        Command(string, string); // Parameterized constructor 2
        ~Command(); // Destructor

        // Accessors
        string getCommand(), getTransitionsTo(), getEffect();
        int *getValidIn();

        // Mutators
        void setCommand(string), setValidIn(int*, int), setTransitionsTo(string), saveEffect(string);

        void addValidInState(int);

        int validInLength;

        // From Iloggable
        string stringToLog();
    private:
        string command, transitionsTo, effect; // Command name, next state, and dynamic effect of the command
        int *validIn; // Which states it valid in
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

        bool validate(const Command &c); // Checks if the current Command is in the valid state

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