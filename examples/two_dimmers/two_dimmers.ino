#include "ProtoHelper.h"
#include "string.h"
#define PWM_PIN_1 5
#define PWM_PIN_2 7

ProtoHelper &phelper = ProtoHelper::getInstance();   //init the helper

// a callback function that triggers when a command is fully recieved
void onRecieve(Command *command) 
{

    char whichLED = command->getParam(0)->getCharValue();
    int intensity = command->getParam(1)->getIntValue();

    // using a character instead of a full string as commandName is the best Practice
    if (command->getNameAsChar() == 'D')       
    {   
        switch (whichLED)
        {
        case '1':
            analogWrite(PWM_PIN_1, intensity);
            break;
        
        case '2':
            analogWrite(PWM_PIN_2, intensity);
            break;
        }
    }
}

void setup()
{
    phelper.setOnCommandRecievedCallabck(onRecieve); //the OnRecieve callback
    Serial.begin(9600);                              //set baudrate to 9600
}

void loop()
{
    while (Serial.available())
        phelper.loadByte(Serial.read());            //load all bytes from serial bus
}