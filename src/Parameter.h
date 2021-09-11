#ifndef PARAMETER_H
#define PARAMETER_H
#include<stdint.h>


class Parameter {

private:
char*               data = nullptr;
uint8_t             size;

public:
                    Parameter(char* bytes, uint8_t size);
                    ~Parameter();
                    Parameter(const Parameter&);
Parameter&          operator=(const Parameter& src);

float               getFloatValue();
const char*         getStringValue();
char                getCharValue();
int                 getIntValue();
double              getDoubleValue();
long                getLongValue();

};

#endif // PARAMETER_H
