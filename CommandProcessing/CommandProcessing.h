#pragma once

#include <string>
#include <iostream>
#include <fstream>
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

        // TODO: find out when saveEffect() gets called
        // Mutators
        void setCommand(string), setValidIn(int*, int), setTransitionsTo(string), saveEffect(string);

        void addValidInState(int);

        int validInLength;

        string stringToLog(); // From Iloggable
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
        virtual void getCommand(); // Reads and then saves a command from the console

        bool validate(const Command &c); // Checks if the current Command is in the valid state

        int commandsLength;

        string stringToLog(); // From Iloggable
    private:
        GameEngine *engine; // GameEngine on which the CommandProcessor is dependant for states
        Command *commands; // Array of current and past Commands
};

class FileCommandProcessorAdapter : public CommandProcessor {
    public:
        // TODO: did I do this overriding properly?
        void getCommand() override; // Reads and then saves a command from the console

        void readFromFile(string); // Reads (startup) commands sequentially from a file

    private:
        string currentFile;
        int currentLine;
};