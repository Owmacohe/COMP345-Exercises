#include "../Cards/Cards.h"
#include "CommandProcessing.h"
#include "../GameEngine/GameEngine.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"

// Default constructor
Command::Command() {
    command = "";
    validIn = vector<int>();
    transitionsTo = "";
    effect = "";

    cout << "[Command default constructor]" << endl;
}

// Parameterized constructor 1 (unparemeterized Commands)
Command::Command(string c) {
    command = c;
    validIn = vector<int>();
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
    command = c;
    validIn = vector<int>();
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
    cout << "[" + command + " Command destructor]" << endl;
}

// Command stream insertion operator
ostream& operator<<(ostream &strm, const Command &c) {
    string temp = "";

    for (int i : c.validIn) {
        temp += to_string(i) + " | ";
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
vector<int> Command::getValidIn() { return validIn; }
string Command::getTransitionsTo() { return transitionsTo; }
string Command::getEffect() { return effect; }

// Mutators
void Command::setCommand(string c) { command = c; }
void Command::setValidIn(vector<int> v) {
    validIn = vector<int>();

    for (int i : v) {
        validIn.push_back(i);
    }
}
void Command::setTransitionsTo(string t) { transitionsTo = t; }
void Command::saveEffect(string e) {
    effect = e;

    notify(this);
}

// Method to add a new state in which the Command is valid
void Command::addValidInState(int s) { validIn.push_back(s); }

string Command::stringToLog() {
    string logString = "Command entered: " + command + " leading to " + transitionsTo + " and creating the effect of " + effect +"\n";
    return logString;
}

// Default constructor
CommandProcessor::CommandProcessor() {
    // TODO: command line option is set to either read commands from the console or from a given file
        // if from file, set this to FileCommandProcessorAdapter

    engine = NULL;
    commands = vector<Command*>();

    cout << "[CommandProcessor default constructor]" << endl;
}

// Parameterized constructor
CommandProcessor::CommandProcessor(GameEngine *e) {
    // TODO: command line option is set to either read commands from the console or from a given file
        // if from file, set this to FileCommandProcessorAdapter

    engine = e;
    commands = vector<Command*>();

    cout << "[CommandProcessor parameterized constructor]" << endl;
}

// Destructor
CommandProcessor::~CommandProcessor() {
    for (Command *i : commands) {
        delete i;
        i = NULL;
    }

    cout << "[CommandProcessor destructor]" << endl;
}

// CommandProcessor stream insertion operator
ostream& operator<<(ostream &strm, const CommandProcessor &cp) {
    string temp = "";

    for (Command *i : cp.commands) {
        temp += i->getCommand() + " | ";
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
vector<Command*> CommandProcessor::getCommands() { return commands; }
GameEngine *CommandProcessor::getEngine() { return engine; }

// Mutators
void CommandProcessor::setEngine(GameEngine *e) {
    delete engine;
    engine = e;
}
void CommandProcessor::setCommands(vector<Command*> c) {
    for (Command *i : commands) {
        delete i;
        i = NULL;
    }

    c = vector<Command*>();

    for (Command *j : c) {
        commands.push_back(j);
    }
}

// Gets command from console
Command *CommandProcessor::readCommand() {
    string word1, word2;
    cin >> word1 >> word2;

    if (word1 != "" && word2 == "") {
        return new Command(word1);
    }
    else if ( word1 != "" && word2 != "") {
        return new Command(word1, word2);
    }
    else {
        cout << "Invalid command!" << endl;
        return NULL;
    }
}

// Stores the gotten Command in the array
void CommandProcessor::saveCommand(Command *c) {
    commands.push_back(c);

    notify(this); // FROM SUBJECT
}

// Reads and then saves a command from the console
void CommandProcessor::getCommand() {
    Command *temp = readCommand();
    saveCommand(temp);
}

// Checks if the current Command is in the valid state
bool CommandProcessor::validate(Command *c) {
    bool isValid = false;

    for (int i : c->getValidIn()) {
        if (i == engine->getState()) {
            isValid = true;
            break;
        }
    }

    if (isValid) {
        return true;
    }
    else {
        cout << "Command " + c->getCommand() + " is invalid in the current state!" << endl;
        return false;
    }
}

string CommandProcessor::stringToLog() {
    string logString = " Saved the following command to the CommandProcessor: " + commands[commands.size() - 1]->getEffect() +"\n";
    return logString;
}

Command *FileLineReader::readLineFromFile(string f, int l) {
    ifstream input(f);
    string line;

    // Checking to see if the file can even be read from
    if (!getline(input, line)) {
        cout << "Unable to read file: " << f << endl;
    }
    else {
        for (int i = 0; i < l; i++) {
            getline(input, line);
        }
    }

    input.close();

    string word1 = "";
    string word2 = "";
    bool hasReachedSpace = false;

    for (char i : line) {
        if (!hasReachedSpace) {
            if (i == ' ') {
                hasReachedSpace = true;
            }
            else {
                word1 += i;
            }
        }
        else {
            if (i != '<' && i != '>') {
                word2 += i;
            }
        }
    }

    if (word2.length() > 0) {
        return new Command(word1, word2);
    }
    else {
        return new Command(word1);
    }
}

// Default constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter() {
    currentFile = "";
    currentLine = 0;
    flr = new FileLineReader();
}

// Parameterized constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(string f) {
    currentFile = f;
    currentLine = 0;
    flr = new FileLineReader();
}

// Destructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete flr;
    flr = NULL;
}

// FileCommandProcessorAdapter stream insertion operator
ostream& operator<<(ostream &strm, const FileCommandProcessorAdapter &fcpa) {
    string temp = "";

    for (Command *i : fcpa.commands) {
        temp += i->getCommand() + " | ";
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
    Command *temp = flr->readLineFromFile(currentFile, currentLine);
    currentLine++;
    saveCommand(temp);
}