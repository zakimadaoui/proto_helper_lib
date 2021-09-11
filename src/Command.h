#ifndef PROTO_COMMAND_H
#define PROTO_COMMAND_H
#define MAX_PARAMS_SIZE 15

#include "Parameter.h"

class ProtoHelper;

class Command
{
private:
    Parameter*  params[MAX_PARAMS_SIZE];
    char*       name = nullptr;
    int         params_size = 0;


                Command();
                ~Command();
                Command(const Command& command) = delete; //no copy allowed
    Command&    operator=(const Command&) = delete; // no assignment allowed
    void        setCommandName(char *name, uint8_t size);
    void        addParam(Parameter *param);

public:

    Parameter*  getParam(uint8_t index);
    const char* getCommandName();
    char        getNameAsChar();
    uint8_t     getParamsSize(){return params_size;}
 

    friend class ProtoHelper;
};

#endif
