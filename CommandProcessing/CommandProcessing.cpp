#include "CommandProcessing.h"

Command::Command() {
    command = "";
    validInLength = 0;
    validIn = new string[validInLength];
    transitionsTo = "";
    effect = "";

    cout << "[Command default constructor]" << endl;
}

Command::Command(string c) {
    command = c;
    validInLength = 1;
    validIn = new string[validInLength];
    effect = "";

    if (c == "validatemap") {
        this->addValidInState("maploaded");
        transitionsTo = "mapvalidated";
    }
    else if (c == "gamestart") {
        this->addValidInState("playersadded");
        transitionsTo = "assignreinforcement";
    }
    else if (c == "replay") {
        this->addValidInState("win");
        transitionsTo = "start";
    }
    else if (c == "quit") {
        this->addValidInState("win");
        transitionsTo = "exit program";
    }

    cout << "[" + command + " Command parameterized constructor 1]" << endl;
}

Command::Command(string c, string p) {
    command = c + " <" + p + ">";
    validInLength = 2;
    validIn = new string[validInLength];
    effect = "";

    if (c == "loadmap") {
        this->addValidInState("start");
        this->addValidInState("maploaded");
        transitionsTo = "maploaded";
    }
    else if (c == "addplayer") {
        this->addValidInState("mapvalidated");
        this->addValidInState("playersadded");
        transitionsTo = "playersadded";
    }

    cout << "[" + command + " Command parameterized constructor 2]" << endl;
}

Command::~Command() {
    validInLength = 0;
    delete[] validIn;
    validIn = NULL;

    cout << "[" + command + " Command destructor]" << endl;
}

string Command::getCommand() { return command; }
string *Command::getValidIn() { return validIn; }
string Command::getTransitionsTo() { return transitionsTo; }
string Command::getEffect() { return effect; }

void Command::setCommand(string c) { command = c; }
void Command::setValidIn(string *v, int l) {
    delete[] validIn;
    validIn = new string[l];

    for (int i = 0; i < l; i++) {
        validIn[i] = v[i];
    }

    validInLength = l;
}
void Command::setTransitionsTo(string t) { transitionsTo = t; }
void Command::setEffect(string e) { effect = e; }

void Command::addValidInState(string s) {
    string *temp = new string[validInLength + 1]; // Creating a new array (1 size larger)

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

string Command::stringToLog(){
    string logString = "STRING FORMED FROM ATTRIBUTES OR STATE OF SUBJECT FOR IT TO BE THE RETURN STRING OF THIS METHOD";
    return logString;}

CommandProcessor::CommandProcessor() {
    commandsLength = 0;
    commands = new Command[commandsLength];

    cout << "[CommandProcessor default constructor]" << endl;
}

CommandProcessor::~CommandProcessor() {
    commandsLength = 0;
    delete[] commands;
    commands = NULL;

    cout << "[CommandProcessor destructor]" << endl;
}

Command *CommandProcessor::getCommands() { return commands; }

void CommandProcessor::setCommands(Command *c, int l) {
    delete[] commands;
    commands = new Command[l];

    for (int i = 0; i < l; i++) {
        commands[i] = c[i];
    }

    commandsLength = l;
}

void CommandProcessor::readCommand() {
    // Read from console
    // Create appropriate Command
    // Call saveCommand() to save the Command
    // Execute the Command's effects
    // Call saveEffects() to save the Command's effects
}

void CommandProcessor::saveCommand(Command c) {
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

Command CommandProcessor::getCommand() { return commands[0]; }

void CommandProcessor::saveEffect(string e) {
    commands[0].setEffect(e);

    notify(this); // FROM SUBJECT ---- IN MY DIAGRAM PART 5 SAVEEFFECT IS IN COMMAND NOT COMMANDPROCESSOR, ERROR ASSIGNMENT? DO YOU HAVE AN EQUIVALENT IN COMMAND? IN FILECOMMAND?
}

bool CommandProcessor::validate() {
    // Uses getCommand().getValidIn() to get the states the current command is valid in
    // Compares it with the GameEngine's current state
    // True if current state is contained, false otherwise
}

string CommandProcessor::stringToLog(){
    string logString = "STRING FORMED FROM ATTRIBUTES OR STATE OF SUBJECT FOR IT TO BE THE RETURN STRING OF THIS METHOD";
    return logString;}

void FileCommandProcessorAdapter::readFromFile() {
    // Uses CommandProcessor methods (readCommand() (or variant) in particular)
    // Does the same as if reading from console
    // But instead reads line by line in a file
}

string FileCommandProcessorAdapter::stringToLog(){
    string logString = "STRING FORMED FROM ATTRIBUTES OR STATE OF SUBJECT FOR IT TO BE THE RETURN STRING OF THIS METHOD";
    return logString;}