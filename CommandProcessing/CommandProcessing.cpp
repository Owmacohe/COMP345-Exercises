#include "../Cards/Cards.h"
#include "CommandProcessing.h"
#include "../GameEngine/GameEngine.h"
#include "../LoggingObserver/LoggingObserver.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"

// Default constructor
Command::Command() {
    command = "";
    validInLength = 0;
    validIn = new int[validInLength];
    transitionsTo = "";
    effect = "";

    cout << "[Command default constructor]" << endl;
}

// Parameterized constructor 1 (unparemeterized Commands)
Command::Command(string c) {
    command = c;
    validInLength = 1;
    validIn = new int[validInLength];
    effect = "";

    if (c == "validatemap") {
        this->addValidInState(2);
        transitionsTo = "mapvalidated";
    }
    else if (c == "gamestart") {
        this->addValidInState(4);
        transitionsTo = "assignreinforcement";
    }
    else if (c == "replay") {
        this->addValidInState(8);
        transitionsTo = "start";
    }
    else if (c == "quit") {
        this->addValidInState(8);
        transitionsTo = "exit program";
    }
    else {
        cout << "Invalid command!" << endl;
    }

    cout << "[" + command + " Command parameterized constructor]" << endl;
}

// Parameterized constructor 2 (paremeterized Commands)
Command::Command(string c, string p) {
    command = c + " <" + p + ">";
    validInLength = 2;
    validIn = new int[validInLength];
    effect = "";

    if (c == "loadmap") {
        this->addValidInState(1);
        this->addValidInState(2);
        transitionsTo = "maploaded";
    }
    else if (c == "addplayer") {
        this->addValidInState(3);
        this->addValidInState(4);
        transitionsTo = "playersadded";
    }
    else {
        cout << "Invalid command!" << endl;
    }

    cout << "[" + command + " Command parameterized constructor]" << endl;
}

// Destructor
Command::~Command() {
    validInLength = 0;
    delete[] validIn;
    validIn = NULL;

    cout << "[" + command + " Command destructor]" << endl;
}

// Accessors
string Command::getCommand() { return command; }
int *Command::getValidIn() { return validIn; }
string Command::getTransitionsTo() { return transitionsTo; }
string Command::getEffect() { return effect; }

// Mutators
void Command::setCommand(string c) { command = c; }
void Command::setValidIn(int *v, int l) {
    delete[] validIn;
    validIn = new int[l];

    for (int i = 0; i < l; i++) {
        validIn[i] = v[i];
    }

    validInLength = l;
}
void Command::setTransitionsTo(string t) { transitionsTo = t; }
void Command::saveEffect(string e) {
    effect = e;

    notify(this);
}

// Method to add a new state in which the Command is valid
void Command::addValidInState(int s) {
    int *temp = new int[validInLength + 1]; // Creating a new array (1 size larger)

    // Copying the old elements into the new array
    for (int i = 0; i < validInLength; i++) {
        temp[i] = validIn[i];
    }

    // Freeing the old memory and setting the new address
    delete[] validIn;
    validIn = temp;

    // Setting the new element and incrementing the size variable
    validIn[validInLength] = s;
    validInLength++;
}

string Command::stringToLog() {
    string logString = "Command entered: " + command + " leading to " + transitionsTo + " and creating the effect of " + effect +"\n";
    return logString;
}

// Default constructor
CommandProcessor::CommandProcessor() {
    engine = new GameEngine;

    commandsLength = 0;
    commands = new Command[commandsLength];

    cout << "[CommandProcessor default constructor]" << endl;
}

// Parameterized constructor
CommandProcessor::CommandProcessor(GameEngine e) {
    engine = new GameEngine(e);

    commandsLength = 0;
    commands = new Command[commandsLength];

    cout << "[CommandProcessor parameterized constructor]" << endl;
}

// Destructor
CommandProcessor::~CommandProcessor() {
    delete engine;
    engine = NULL;

    delete[] commands;
    commands = NULL;
    commandsLength = 0;

    cout << "[CommandProcessor destructor]" << endl;
}

// Accessors
Command *CommandProcessor::getCommands() { return commands; }
GameEngine *CommandProcessor::getEngine() { return engine; }

// Mutators
void CommandProcessor::setCommands(Command *c, int l) {
    delete[] commands;
    commands = new Command[l];

    for (int i = 0; i < l; i++) {
        commands[i] = c[i];
    }

    commandsLength = l;
}
void CommandProcessor::setEngine(GameEngine *e) {
    delete engine;
    engine = e;
}

// Gets command from console
Command CommandProcessor::readCommand() {
    string temp;
    cin >> temp;

    string word1 = "";
    string word2 = "";
    bool hasReachedSpace = false;

    for (char i : temp) {
        if (!hasReachedSpace) {
            if (i == ' ') {
                hasReachedSpace = true;
            }
            else {
                word1 += i;
            }
        }
        else {
            word2 += i;
        }
    }

    if (word1 != "" && word2 == "") {
        return Command(word1);
    }
    else if ( word1 != "" && word2 != "") {
        return Command(word1, word2);
    }
    else {
        cout << "Invalid command!" << endl;
        Command c;
        return c;
    }
}

// Stores the gotten Command in the array
void CommandProcessor::saveCommand(const Command &c) {
    Command *temp = new Command[commandsLength + 1]; // Creating a new array (1 size larger)

    // Copying the old elements into the new array
    for (int i = 0; i < commandsLength; i++) {
        temp[i] = commands[i];
    }

    // Freeing the old memory and setting the new address
    delete[] commands;
    commands = temp;

    // Setting the new element and incrementing the size variable
    commands[commandsLength] = c;
    commandsLength++;

    notify(this); // FROM SUBJECT
}

// Reads and then saves a command from the console
void CommandProcessor::getCommand() {
    Command temp = readCommand();
    saveCommand(temp);
}

// Checks if the current Command is in the valid state
bool CommandProcessor::validate(const Command &c) {
    Command temp = Command(c);
    bool isValid = false;

    for (int i = 0; i < temp.validInLength; i++) {
        if (temp.getValidIn()[i] == engine->getState()) {
            isValid = true;
        }
    }

    if (isValid) {
        return true;
    }
    else {
        cout << "Command " + temp.getCommand() + " is invalid in the current state!" << endl;
        return false;
    }
}

string CommandProcessor::stringToLog() {
    string logString = " Saved the following command to the CommandProcessor: " + commands[commandsLength-1].getEffect() +"\n";
    return logString;
}

// Reads and then saves a command from a file
void FileCommandProcessorAdapter::getCommand() {
    ifstream input(currentFile);
    string line;

    // Checking to see if the file can even be read from
    if (!getline(input, line)) {
        cout << "Unable to read file: " << currentFile << endl;
    }
    else {
        for (int i = 0; i < currentLine; i++) {
            getline(input, line);
        }

        currentLine++;
    }

    input.close();

    Command temp = Command(line);
    saveCommand(temp);
}

// Reads (startup) commands sequentially from a file
void FileCommandProcessorAdapter::readFromFile(string f) {
    currentFile = f;

    getEngine()->startupPhase();
}
