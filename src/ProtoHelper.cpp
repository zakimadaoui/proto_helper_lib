#include "ProtoHelper.h"
#include "Command.h"
#include<stdint.h>


//========================== Functions implementation ==============================


ProtoHelper::ProtoHelper(){}

ProtoHelper::~ProtoHelper(){
    delete current_command;
}


ProtoHelper& ProtoHelper::getInstance() {
    static ProtoHelper instance_;
    return instance_;
}

void ProtoHelper::setOnCommandRecievedCallabck(void (*callback)(Command* cmnd)){
    this->callback = callback;
}


    //here we parse the command
void ProtoHelper::loadByte(char byte){

    static char     str_buff[27]; //buffer for the current parameter or cmnd name 
    static uint8_t  index = 0; //index for current buffer chararchter

    switch (current_state) {

    case BEGIN:
        
        if(byte == '>') {
            current_command = new Command(); 
            current_state = OPCODE_CONCAT;
        }
        break;

    case OPCODE_CONCAT:

        //TODO:apply the 27 buffer limit to the app (no param value can be 27+ chars long)!
        if(index >= 27) break;
        
            //case of commands with no parameters
            if(byte == '<')
            {
            str_buff[index] = '\0'; // don't forget to terminate the string !
            index++;
            current_command->setCommandName(str_buff, index);
            current_state = BEGIN;
            callback(current_command);
            delete current_command;
            index = 0;
            break;
            }

        // normal case: having one or more parameters, so switch to PARAM_CONCAT
        if(byte == ','){
            str_buff[index] = '\0'; // don't forget to terminate the string !
            index++;
            current_command->setCommandName(str_buff, index);
            current_state = PARAM_CONCAT;
            index = 0;
            break;
        }

        str_buff[index] = byte;
        index++;
        break;

   
    case PARAM_CONCAT:

        //TODO:apply the 27 buffer limit to the app (no param value can be 27+ chars long)!
        if(index >= 27) break;
    
        if(byte == ',' || byte == '<')
        {
            str_buff[index] = '\0'; // don't forget to terminate the string !
            index++;
            current_command->addParam(new Parameter(str_buff,index));//index represents nbrBytes || size
            index = 0;

            if(byte == '<')
            {
                current_state = BEGIN;
                callback(current_command);
                delete current_command;
            }

            break;
        }

        str_buff[index] = (char)byte;
        index++;
        break;
    }

}

void ProtoHelper::loadBytesFromBuffer(char *buffer, uint8_t buff_size)
{
    for (uint8_t i = 0; i < buff_size; i++) this->loadByte(buffer[i]);
}
