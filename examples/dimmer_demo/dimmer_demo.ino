#include "ProtoHelper.h"
#include "string.h"
#define PWM_PIN 5

ProtoHelper &phelper = ProtoHelper::getInstance();   //init the helper

// a callback function that triggers when a command is fully recieved
void onRecieve(Command *command){
    // The GUI has a Knob widget that sends the command :
    // "> DIMM, integer(intensity)" and 'intensity' varries from 0 to 255
    
    if (strcmp("DIMM", command->getCommandName()) == 0){
        int intensity = command->getParam(0)->getIntValue();
        analogWrite(PWM_PIN, intensity);
    }

    // OR, to avoid using string comparision use getNameAsChar() 
    // with commandName='D' instead of 'DIMM'(Best Practice)
    /*
    if (command->getNameAsChar() == 'D')       // the commandName 'D' stands for DIMM
    {
        int intensity = command->getParam(0)->getIntValue();
        analogWrite(PWM_PIN, intensity);
    }
    */
}

void setup(){
    phelper.setOnCommandRecievedCallabck(onRecieve); //the OnRecieve callback
    Serial.begin(9600);                              //set baudrate to 9600
}

void loop(){
    while (Serial.available())
        phelper.loadByte(Serial.read());            //load all bytes from serial bus
}
