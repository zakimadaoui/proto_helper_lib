#ifndef PROTO_HELPER_H
#define PROTO_HELPER_H
#include "Command.h"
#include "Parameter.h"

class ProtoHelper
{
private:
    void                    (*callback)(Command* command);
    void                    (*rawCallback)(char* opcode, char** params, int params_nbr);
    enum state              {BEGIN ,OPCODE_CONCAT , PARAM_CONCAT};
    state                   current_state = BEGIN;
    Command*                current_command;
public:

    //Singletons can not be cloneable
    ProtoHelper(ProtoHelper& other) = delete;

    // //Singletons can not be assigned
    // void operator=(const ProtoHelper&) = delete;

    static ProtoHelper&     getInstance();
    void                    loadByte(char byte);
    void                    loadBytesFromBuffer(char* buffer, uint8_t buff_size); 
    void                    setOnCommandRecievedCallabck(void (*callback)(Command* command));
    ~ProtoHelper();

protected:
    ProtoHelper();
};



#endif
