#pragma once

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#include "../LoggingObserver/LoggingObserver.h"

class GameEngine;

// Class representing one Command that gets executed in (primarily) the startup phase
class Command : public Iloggable, public Subject {
    public:
        Command(); // Default constructor
        Command(string); // Parameterized constructor 1 (unparemeterized Commands)
        Command(string, string); // Parameterized constructor 2 (paremeterized Commands)
        ~Command(); // Destructor
        friend ostream& operator<<(ostream &strm, const Command &c); // Stream insertion operator
        Command& operator = (const Command& toAssign);  // Assignment operator

        // Accessors
        string getCommand(), getTransitionsTo(), getEffect();
        int *getValidIn();

        // Mutators
        void setCommand(string), setValidIn(int*, int), setTransitionsTo(string), saveEffect(string);

        void addValidInState(int); // Method to add a new state in which the Command is valid

        int validInLength; // Array length

        string stringToLog(); // From Iloggable
    private:
        string command, transitionsTo, effect; // Command name, next state, and effect of the command
        int *validIn; // Which states it valid in
};

// Class to get and store Commands from the console for use in drivers and phases
class CommandProcessor : public Iloggable, public Subject {
    public:
        CommandProcessor(); // Default constructor
        CommandProcessor(GameEngine*); // Parameterized constructor
        ~CommandProcessor(); // Destructor
        friend ostream& operator<<(ostream &strm, const CommandProcessor &cp); // Stream insertion operator
        CommandProcessor& operator = (const CommandProcessor& toAssign);  // Assignment operator

        // Accessors
        GameEngine *getEngine();
        Command *getCommands();

        // Mutators
        void setCommands(Command*, int), setEngine(GameEngine*);

        Command readCommand(); // Gets command from console
        void saveCommand(const Command &c); // Stores the gotten Command in the array
        virtual void getCommand(); // Reads and then saves a command from the console

        bool validate(const Command &c); // Checks if the current Command is in the valid state

        int commandsLength; // Array length

        string stringToLog(); // From Iloggable
    protected:
        GameEngine *engine; // GameEngine on which the CommandProcessor is dependant for states
        Command *commands; // Array of current and past Commands
};

// Modified CommandProcessor that instead gets Commands from a file
class FileCommandProcessorAdapter : public CommandProcessor {
    public:
        friend ostream& operator<<(ostream &strm, const FileCommandProcessorAdapter &fcpa); // Stream insertion operator
        FileCommandProcessorAdapter& operator = (const FileCommandProcessorAdapter& toAssign);  // Assignment operator

        void getCommand() override; // Reads and then saves a command from a file

        void readFromFile(string); // Reads (startup) commands sequentially from a file
    private:
        string currentFile; // The current file of commands that is being read from
        int currentLine; // The current line being read in the current file
};