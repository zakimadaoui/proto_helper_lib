#include <string.h>
#include "Command.h"
#include "Parameter.h"

Command::Command(){}

Command::~Command(){
    for(int i=0; i< params_size ; i++) delete params[i];
    delete[] name;
}


// Commands are neither allowed to be copied NOR assigned
// Command::Command(const Command& command){

//    name = command.name;
//    params_size = command.params_size;
//    for(int i = 0; i < params_size; i++)params[i] = command.params[i]; //this will cause an issue !

// }

// Command& Command::operator=(const Command &){
//     return *this;
// }


void Command::setCommandName(char* command_name, uint8_t size){
    this->name = new char[size];
    memcpy(this->name, command_name, size);
}


const char* Command::getCommandName(){
    return name;
}

char Command::getNameAsChar()
{
    return *name;
}

void Command::addParam(Parameter* param){
    params[params_size] = param;
    params_size++;
}


Parameter* Command::getParam(uint8_t index){
    return (index < params_size)? params[index] : nullptr;
}