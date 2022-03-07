#include "../Cards/Cards.h"
#include "CommandProcessing.h"
#include "../GameEngine/GameEngine.h"
#include "../LoggingObserver/LoggingObserver.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"

Command::Command() {
    command = "";
    validInLength = 0;
    validIn = new int[validInLength];
    transitionsTo = "";
    effect = "";

    cout << "[Command default constructor]" << endl;
}

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

Command::~Command() {
    validInLength = 0;
    delete[] validIn;
    validIn = NULL;

    cout << "[" + command + " Command destructor]" << endl;
}

string Command::getCommand() { return command; }
int *Command::getValidIn() { return validIn; }
string Command::getTransitionsTo() { return transitionsTo; }
string Command::getEffect() { return effect; }

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

    notify(this); // FROM SUBJECT ---- IN MY DIAGRAM PART 5 SAVEEFFECT IS IN COMMAND NOT COMMANDPROCESSOR, ERROR ASSIGNMENT? DO YOU HAVE AN EQUIVALENT IN COMMAND? IN FILECOMMAND?
}

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
    string logString = "STRING FORMED FROM ATTRIBUTES OR STATE OF SUBJECT FOR IT TO BE THE RETURN STRING OF THIS METHOD";
    return logString;
}

CommandProcessor::CommandProcessor() {
    engine = new GameEngine;

    commandsLength = 0;
    commands = new Command[commandsLength];

    cout << "[CommandProcessor default constructor]" << endl;
}

CommandProcessor::CommandProcessor(GameEngine e) {
    engine = new GameEngine(e);

    commandsLength = 0;
    commands = new Command[commandsLength];

    cout << "[CommandProcessor parameterized constructor]" << endl;
}

CommandProcessor::~CommandProcessor() {
    delete engine;
    engine = NULL;

    delete[] commands;
    commands = NULL;
    commandsLength = 0;


    cout << "[CommandProcessor destructor]" << endl;
}

Command *CommandProcessor::getCommands() { return commands; }
GameEngine *CommandProcessor::getEngine() { return engine; }

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

void CommandProcessor::getCommand() {
    Command temp = readCommand();

    saveCommand(temp);
}

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
        cout << "INVALID COMMANDPROCESSOR: given Command is invalid!" << endl;
        return false;
    }
}

string CommandProcessor::stringToLog() {
    string logString = "STRING FORMED FROM ATTRIBUTES OR STATE OF SUBJECT FOR IT TO BE THE RETURN STRING OF THIS METHOD";
    return logString;
}

void FileCommandProcessorAdapter::readFromFile() {
    // Uses CommandProcessor methods (readCommand() (or variant) in particular)
    // Does the same as if reading from console
    // But instead reads line by line in a file
}

string FileCommandProcessorAdapter::stringToLog() {
    string logString = "STRING FORMED FROM ATTRIBUTES OR STATE OF SUBJECT FOR IT TO BE THE RETURN STRING OF THIS METHOD";
    return logString;
}