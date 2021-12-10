# ProtoHelper library
A helper library for **Proto+: the quick GUI creator for Embedded systems**

[![GitHub version](https://img.shields.io/github/v/release/zakimadaoui/proto_helper_lib)](google.com)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](google.com)
__________

![image](https://drive.google.com/uc?export=view&id=1CcuXGqiwDxphvmJf93xjnD__VCwZL1_f)

Proto+ is an android tool that allows you to create Graphical User Interfaces for your Embedded  projects and prototypes in few minutes !  

The GUIs can be created quickly using drag and drop widgets like: Buttons, Sliders, and knobs. These widgets are highly customizable whether
it is in terms of the physical properties such as the size, color and orientations, but also in terms of the commands that will be sent to
the micro-controller. 

Proto+ can connect to your micro-controller or computer via Bluetooth, TCP/IP or even via UART, and on top of that, the C++ **HelperLibrary** will take care of parsing the recieved commands, generating events when commands are fully recieved and converted into objects, to keep your code clean and organized.


[Donwload app from the Play Store](https://play.google.com/store/apps/details?id=com.zmdev.protoplus)


## Installing in Arduino IDE

You can download this library as a [`ZIP`](https://github.com/zakimadaoui/proto_helper_lib/archive/refs/heads/main.zip) file and import it into the IDE. You can check [this guide](https://www.arduino.cc/en/guide/libraries#toc4) on Importing a .zip Library in Arduino IDE.


**NB:** you can use this library with any other framework or micro-controller as long as the programming language used is C++.

## ProtoHelper Functionality

* This library takes care of processing the commands recieved in the micro-controller side after a user interaction with the Graphical Interfaces created using the **Proto+** mobile app. 
* It understands the command format generated by the mobile application and it efficiently converts the recieved data into `Command` and `Parameter` objects. In addition, it is also event driven so it generates an event after a command is fully recieved and parsed.


### Command structure

A command in **Proto+** is structured in the following manner:

\> `CommandName`, `Parameter_0`, `Parameter_1`, .... `Parameter_N`<  


* **CommandName:** this is generaly a charachter sequence that allows identifying the different commands and their functionality. For example, a command that starts with commandName='MOVE' or commandName='M' can be interpreted by the micro-controller as a signal to more a servo motor.

* **Parameters:** generally hold the data generated at user interaction. For instance, if a user moves a Slider to the right then one of the parameters of the command that gets generated will varry as the user continues sliding to the right.

What makes **Proto+** very powerfull is that the user can create his own custom commands which contain all the flags that he needs and pick a suitable commandName. Then *Link* those commands to the preferred Widgets/Components. 

To allow this customizibility, a `Parameter` can be either a:

* **Variable Parameters:** These are the parameters that hold the variable data that the Widgets/Components generate. The *ORDER* and the *NUMBER* of these parameters in a certain command is dictated by the Widget/Component that the user wants to link the custom command to it.

* **Constant Parameters:** These parameters allow you to specify flags that permit the micro-controller later to take cetain decisions. The *ORDER* and the *NUMBER* of these parameters in a certain command does not matter .


A good example for this would be creating a custom command for a JoyStick widget. We can choose the commandName to be 'JOY'. In order for the command to be compatible with this widget we must have **2 variable parameters** in the following order: the first for X_value, and the second for Y_value. So the command will be as follows:  
\> `JOY`, `float(X_val)`, `float(Y_val)`<

However, if we want to have two JoySticks that send the same command, we want to micro-controller to know which one we are interacting with. So we use a **Constant Parameter** to solve that. So, we can add a constant parameter after the command name which indicates which JoyStick is being used. So we create two commands as follows:  
\> `JOY`, `int(1)`, `float(X_val)`, `float(Y_val)`<  for Joystick 1  
\> `JOY`, `int(2)`, `float(X_val)`, `float(Y_val)`<  for Joystick 2  

 
## Usage

First you need to include the header file of the library and get an instance of the Helper class as follows:

```cpp
#include"ProtoHelper.h"

ProtoHelper& pHelper = ProtoHelper::getInstance();
```

In your setup function, you must set the callback function as follows:


```cpp
void onReceive(Command* command){
// your logic
}

void setup(){
 pHelper.setOnCommandRecievedCallabck(onRecieve);
}
```

The most important step is to feed the recieved data into the helper, which can be done as follows:

```cpp
void loop(){

     //load all bytes from serial bus
     while (Serial.available()) pHelper.loadByte(Serial.read());     
     
     //Or alternatively pass a buffer (Not recommended)
     pHelper.loadByte(buffer, buffer_size)); // the buffer is a char[] or char*
}
```

### Command API

When the `onRecieve()` function is called you get a `Command*` that you can use to retrieve the command name and the parameters:

```cpp
void onReceive(Command* command){

//get command same as a character sequence
char* commandName = command->getCommandName();

//get commandName as a single charachter (BEST PRACTICE)
char commandName  = command->getNameAsChar();

// get your parameters and convert them to the data type that you need

int   param0 = command->getParam(0)->getIntValue();;
float param1 = command->getParam(1)->getFloatValue();;
char* param2 = command->getParam(2)->getStringValue();

// your logic ...

}
```


## Examples

You can find some examples on the examples folder or from the examples section in the arduino IDE, Also you should check [this Youtube Playlist(COMING SOON)](google.com) on how to create your first project with proto+.



