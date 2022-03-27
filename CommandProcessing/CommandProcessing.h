#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#include "../LoggingObserver/LoggingObserver.h"

class GameEngine;

// Class representing one Command that gets executed in (primarily) the startup phase
class Command :public Iloggable, public Subject {
    public:
        Command(); // Default constructor
        Command(string); // Parameterized constructor 1 (un-parameterized Commands)
        Command(string, string); // Parameterized constructor 2 (parameterized Commands)
        Command(const Command &c); // Copy constructor
        ~Command(); // Destructor
        friend ostream& operator<<(ostream &strm, const Command &c); // Stream insertion operator
        Command& operator = (const Command& toAssign);  // Assignment operator

        // Accessors
        string getCommand(), getTransitionsTo(), getEffect();
        vector<int> getValidIn();

        // Mutators
        void setCommand(string), setValidIn(vector<int>), setTransitionsTo(string), saveEffect(string);

        void addValidInState(int); // Method to add a new state in which the Command is valid

        string stringToLog(); // From Iloggable
    private:
        string command, transitionsTo, effect; // Command name, next state, and effect of the command
        vector<int> validIn; // Which states it valid in
};

// Class to get and store Commands from the console for use in drivers and phases
class CommandProcessor : public Iloggable, public Subject {
    public:
        CommandProcessor(); // Default constructor
        CommandProcessor(GameEngine*); // Parameterized constructor
        CommandProcessor(const CommandProcessor &cp); // Copy constructor
        ~CommandProcessor(); // Destructor
        virtual ostream& write(ostream &strm) const; // Stream insertion operator (virtual for derived class)
        friend ostream& operator<<(ostream &strm, CommandProcessor const &cp) { return cp.write(strm); }; // Stream insertion operator
        CommandProcessor& operator = (const CommandProcessor& toAssign);  // Assignment operator

        // Accessors
        GameEngine *getEngine();
        vector<Command*> getCommands();

        // Mutators
        void setEngine(GameEngine*), setCommands(vector<Command*>);

        Command *readCommand(); // Gets command from console
        void saveCommand(Command*); // Stores the gotten Command in the array
        virtual void getCommand(); // Reads and then saves a command from the console

        bool validate(Command*); // Checks if the current Command is in the valid state

        string stringToLog(); // From Iloggable
    protected:
        GameEngine *engine; // GameEngine on which the CommandProcessor is dependant for states
        vector<Command*> commands; // Array of current and past Commands
};

// Class used by FileCommandProcessorAdapter to read sequential lines from a file
class FileLineReader {
    public:
        Command *readLineFromFile(string, int); // Reads the given line from the given file and creates a Command out of it
};

// Modified CommandProcessor that instead gets Commands from a file
class FileCommandProcessorAdapter : public CommandProcessor {
    public:
        FileCommandProcessorAdapter(); // Default constructor
        FileCommandProcessorAdapter(string); // Parameterized constructor
        FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fcpa); // Copy constructor
        ~FileCommandProcessorAdapter(); // Destructor

        ostream& write(ostream &strm) const override; // Stream insertion operator
        FileCommandProcessorAdapter& operator = (const FileCommandProcessorAdapter& toAssign);  // Assignment operator

        // Accessors
        string getCurrentFile();
        int getCurrentLine();

        // Mutators
        void setCurrentFile(string), setCurrentLine(int);
        string stringToLog(); // From Iloggable

        void getCommand() override; // Reads and then saves a command from a file
    private:
        FileLineReader *flr; // FileLineReader used to each line sequentially
        string currentFile; // The current file of commands that is being read from
        int currentLine; // The current line being read in the current file
};