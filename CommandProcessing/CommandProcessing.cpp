#include "CommandProcessing.h"
#include "../GameEngine/GameEngine.h"

// Free method to split a given string into a pointer array based on a given delimiter
string *stringSplit(string s, char delim) {
    int indexChecker = 0;
    int splitLength = 1;
    string *result = new string[splitLength];
    string temp;

    // Looping through all the characters in the string
    for (char i : s) {
        // Adding to the current word if a delimiter has not been reached
        if (i != delim) {
            temp += i;
        }

        // Adding the neew word to the pointer array if a delimiter or the end has been reached
        if (i == delim || indexChecker == s.length() - 1) {
            string *tempResult = new string[splitLength + 1];
            copy(result, result + splitLength, tempResult);

            delete[] result;
            result = new string[splitLength + 1];

            for (int j = 0; j < splitLength; j++) {
                result[j] = tempResult[j];
            }

            result[splitLength] = temp;

            delete[] tempResult;

            splitLength++;
            temp = "";
        }

        indexChecker++;
    }

    result[0] = to_string(splitLength - 1); // Making the first element of the array the length

    return result;
}

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
    else {
        cout << "Invalid command!" << endl;
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
    else {
        cout << "Invalid command!" << endl;
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

    commandsLength = 0;
    delete[] commands;
    commands = NULL;

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

    string *split = stringSplit(temp, ' ');
    int splitLength = stoi(split[0]);

    if (splitLength == 1) {
        return Command(split[1]);
    }
    else if (splitLength == 2) {
        return Command(split[1], split[2]);
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

    // Execute the Command's effects
    // Call saveEffects() to save the Command's effects
}

void CommandProcessor::saveEffect(string e) {

    commands[commandsLength - 1].setEffect(e);

    notify(this); // FROM SUBJECT ---- IN MY DIAGRAM PART 5 SAVEEFFECT IS IN COMMAND NOT COMMANDPROCESSOR, ERROR ASSIGNMENT? DO YOU HAVE AN EQUIVALENT IN COMMAND? IN FILECOMMAND?
}

bool CommandProcessor::validate() {
    /*
    Command temp = commands[commandsLength - 1];
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
        cout << "INVALID COMMANDPROCESSOR: current Command is invalid!" << endl;
        return false;
    }
    */
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