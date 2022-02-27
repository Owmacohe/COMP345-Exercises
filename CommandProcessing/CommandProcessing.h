#pragma once

#include <string>
#include <iostream>
using namespace std;

class Command {
    public:
        Command(); // Default constructor

        // Accessors
        string getCommand(), *getValidIn(), getTransitionsTo(), getEffect();

        // Mutators
        void setCommand(), setValidIn(), setTransitionsTo(), setEffect();
    private:
        string command, *validIn, transitionsTo, effect; // Command name, which states it valid in, next state, and dynamic effect of the command
};

class CommandProcessor {
    public:
        CommandProcessor(); // Default constructor

        // Accessors
        Command *getCommands();

        // Mutators
        void setCommands();

        void readCommand(); // Gets command from console
        void saveCommand(); // Stores the gotten Command in the array
        Command getCommand(); // Gets the current Command (front of the array)
        void saveEffect(); // Stores the result of the current Command in the current Command

        bool validate(); // Checks if the current Command is in the valid state
    private:
        Command *commands; // Array of current and past Commands
};

class FileCommandProcessorAdapter {
    public:
        void readFromFile(); // Reads commands sequentially from a file
};