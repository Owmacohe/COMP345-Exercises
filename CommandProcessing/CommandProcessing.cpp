#include "../Cards/Cards.h"
#include "CommandProcessing.h"
#include "../GameEngine/GameEngine.h"
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
    validInLength = 0;
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
    validInLength = 0;
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

// Command stream insertion operator
ostream& operator<<(ostream &strm, const Command &c) {
    string temp = "";

    for (int i = 0; i < c.validInLength; i++) {
        temp += to_string(c.validIn[i]) + " | ";
    }

    return strm <<
        "[COMMAND PRINT: " << c.command << "]" <<
        endl << "[--- Transitions to: " << c.transitionsTo << " ---]" <<
        endl << "[--- Effect: " << c.effect << " ---]" <<
        endl << "[--- Valid in: " << temp.substr(0, temp.length() - 3) << " ---]";
}

// Command assignment operator
Command& Command::operator = (const Command& toAssign) {
    command = toAssign.command;
    transitionsTo = toAssign.transitionsTo;
    effect = toAssign.effect;
    validIn = toAssign.validIn;
    return *this;
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
    commandsLength = 0;
    commands = new Command[commandsLength];

    cout << "[CommandProcessor default constructor]" << endl;
}

// Parameterized constructor
CommandProcessor::CommandProcessor(GameEngine *e) {
    engine = e;

    commandsLength = 0;
    commands = new Command[commandsLength];

    cout << "[CommandProcessor parameterized constructor]" << endl;
}

// Destructor
CommandProcessor::~CommandProcessor() {
    delete[] commands; // TODO: for some reason, this causes errors...
    commands = NULL;
    commandsLength = 0;

    cout << "[CommandProcessor destructor]" << endl;
}

// CommandProcessor stream insertion operator
ostream& operator<<(ostream &strm, const CommandProcessor &cp) {
    string temp = "";

    for (int i = 0; i < cp.commandsLength; i++) {
        temp += cp.commands[i].getCommand() + " | ";
    }

    return strm <<
        "[COMMANDPROCESSOR PRINT]" <<
        endl << "[--- Engine: " << cp.engine->getState() << " ---]" << // TODO: should the engine be printed in a different way?
        endl << "[--- Commands: " << temp.substr(0, temp.length() - 3) << " ---]";
}

// CommandProcessor assignment operator
CommandProcessor& CommandProcessor::operator = (const CommandProcessor& toAssign) {
    engine = toAssign.engine;
    commands = toAssign.commands;
    return *this;
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
    string word1, word2;
    cin >> word1 >> word2;

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

    cout << engine->getState() << endl;

    for (int i = 0; i < temp.validInLength; i++) {
        if (temp.getValidIn()[i] == engine->getState()) {
            isValid = true;
            break;
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

// FileCommandProcessorAdapter stream insertion operator
ostream& operator<<(ostream &strm, const FileCommandProcessorAdapter &fcpa) {
    string temp = "";

    for (int i = 0; i < fcpa.commandsLength; i++) {
        temp += fcpa.commands[i].getCommand() + " | ";
    }

    return strm <<
        "[FILECOMMANDPROCESSORADAPTER PRINT]" <<
        endl << "[--- Engine: " << fcpa.engine->getState() << " ---]" << // TODO: should the engine be printed in a different way?
        endl << "[--- Commands: " << temp.substr(0, temp.length() - 3) << " ---]" <<
        endl << "[--- Current file: " << fcpa.currentFile << " ---]" <<
        endl << "[--- Current line: " << fcpa.currentLine << " ---]";
}

// FileCommandProcessorAdapter assignment operator
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator = (const FileCommandProcessorAdapter& toAssign) {
    engine = toAssign.engine;
    commands = toAssign.commands;
    currentFile = toAssign.currentFile;
    currentLine = toAssign.currentLine;
    return *this;
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