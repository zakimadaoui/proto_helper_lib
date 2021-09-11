#include"Parameter.h"
#include<string.h>
#include<stdlib.h>


Parameter::Parameter(char* bytes, uint8_t size){

    //allocate the right amount of memory for parameter data
    data = new char[size];
    //copy by block (fastest way possible)
    memcpy(data,bytes, size);
    //set data type (needed later for correction)
}

Parameter::~Parameter(){
    delete[] data;
}

Parameter::Parameter(const Parameter& src){
    size = src.size;
    data = new char[size];
    memcpy(data,src.data, size);
}

Parameter& Parameter::operator=(const Parameter&){
    return *this;
}


const char* Parameter::getStringValue(){
    return data;
}

char Parameter::getCharValue()
{
    return *(data);
}

int Parameter::getIntValue(){
    char* c = data;
    return atoi(c);
    // naive algo
    // int val = 0;
    // while( *c != '\0') {
    //     val = val*10 + (*c++ -'0');
    // }
    // return val;
}


float Parameter::getFloatValue(){
    char* c = data;
    return atof(c);
}


long Parameter::getLongValue(){
    char* c = data;
    return atol(c);
}


double Parameter::getDoubleValue(){
    char* c = data;
    return atof(c);
}
