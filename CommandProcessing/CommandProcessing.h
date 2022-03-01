#pragma once

#include <string>
#include <iostream>
using namespace std;

class Command {
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
    private:
        string command, *validIn, transitionsTo, effect; // Command name, which states it valid in, next state, and dynamic effect of the command
};

class CommandProcessor {
    public:
        CommandProcessor(); // Default constructor
        ~CommandProcessor(); // Destructor

        // Accessors
        Command *getCommands();

        // Mutators
        void setCommands(Command*, int);

        void readCommand(); // Gets command from console
        void saveCommand(Command); // Stores the gotten Command in the array
        Command getCommand(); // Gets the current Command (front of the array)
        void saveEffect(string); // Stores the result of the current Command in the current Command

        bool validate(); // Checks if the current Command is in the valid state

        int commandsLength;
    private:
        Command *commands; // Array of current and past Commands
};

class FileCommandProcessorAdapter {
    public:
        void readFromFile(); // Reads commands sequentially from a file
};