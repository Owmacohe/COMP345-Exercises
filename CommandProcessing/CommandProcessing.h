#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#include "../LoggingObserver/LoggingObserver.h"

/// Forward declaration of GameEngine and Map
class GameEngine;
class Map;

/**
 * Class representing one Command that gets executed in (primarily) the startup phase
 */
class Command :public Iloggable, public Subject {
    public:
        /// Default constructor
        Command();

        /**
        Parameterized constructor for validatemap, gamestart, replay, and quit commands
        @param string command name
        @return the Command created
        */
        Command(string);

        /**
        Parameterized constructor for loadmap and addplayer commands
        @param string command name, string command parameter
        @return the Command created
        */
        Command(string, string);

        /**
        Parameterized constructor for tournament commands
        @param string command name, string Map list, string PlayerStrategies list, int number of games, int max turns
        @return the Command created
        */
        Command(string, string, string, int, int);

        /**
        Copy constructor that creates a deep copy
        @param constant Commands reference
        @return the Commands created
        */
        Command(const Command &c);

        /// Destructor
        ~Command();

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the Command as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream &strm, const Command &c);

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Command reference that will be copied and assigned
        @return Command reference
        */
        Command& operator = (const Command& toAssign);

        /**
        Accessor for the name of the Command
        @param None
        @return string that is the name of the Command
        */
        string getCommand();

        /**
        Accessor for the name of the state the Command transitions to
        @param None
        @return string that is the name of the state the Command transitions to
        */
        string getTransitionsTo();

        /**
        Accessor for the effect of the Command
        @param None
        @return string that is the effect of the Command
        */
        string getEffect();

        /**
        Accessor for the states that the Command is valid in
        @param None
        @return vector of integers that is the states that the Command is valid in
        */
        vector<int> getValidIn();

        /**
        Mutator for the name of the Command
        @param string that is the name of the Command
        @return None
        */
        void setCommand(string);

        /**
        Mutator for the name of the state the Command transitions to
        @param string that is the name of the state the Command transitions to
        @return None
        */
        void setTransitionsTo(string);

        /**
        Mutator for the effect of the Command
        @param string that is the effect of the Command
        @return None
        */
        void saveEffect(string);

        /**
        Mutator for the states that the Command is valid in
        @param vector of integers that is the states that the Command is valid in
        @return None
        */
        void setValidIn(vector<int>);

        /**
        Method to add a new state in which the Command is valid
        @param int new state in which the Command is valid
        @return None
        */
        void addValidInState(int); // Method to add a new state in which the Command is valid

        string stringToLog() override; // From Iloggable

        /// Whether the Command name has been inputted correctly, but the parameters are missing
        bool isPossibleCommand;
    private:
        /// Name of the Command
        string command;
        /// The name of the state the Command transitions to
        string transitionsTo;
        /// Effect of the Command
        string effect;
        /// The states that the Command is valid in
        vector<int> validIn;
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
        vector<string> getMaps(), getPlayerStrategies();
        int getNumberOfGames(), getMaxTurns();

        // Mutators
        void setEngine(GameEngine*), setCommands(vector<Command*>), setMaps(vector<string>), setPlayerStrategies(vector<string>), setNumberOfGames(int), setMaxTurns(int);

        void addMap(string), addPlayerStrategy(string);

        Command *readCommand(); // Gets command from console
        void saveCommand(Command*); // Stores the gotten Command in the array
        virtual void getCommand(); // Reads and then saves a command from the console

        bool validate(Command*); // Checks if the current Command is in the valid state

        string stringToLog() override; // From Iloggable
    protected:
        GameEngine *engine; // GameEngine on which the CommandProcessor is dependant for states
        vector<Command*> commands; // Array of current and past Commands

        vector<string> maps, playerStrategies; // Maps and PlayerStrategies for the tournament
        int numberOfGames, maxTurns; // Number of games and maximum number of turns per game for the tournament
};

// Class used by FileCommandProcessorAdapter to read sequential lines from a file
class FileLineReader {
    public:
        Command *readLineFromFile(CommandProcessor*, string, int); // Reads the given line from the given file and creates a Command out of it
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
        string stringToLog() override; // From Iloggable

        void getCommand() override; // Reads and then saves a command from a file
    private:
        FileLineReader *flr; // FileLineReader used to each line sequentially
        string currentFile; // The current file of commands that is being read from
        int currentLine; // The current line being read in the current file
};