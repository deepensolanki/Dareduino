#include <avr/io.h>

#define INPUT 0
#define OUTPUT 1

void pinConfig(int, int);
void pinWrite(int, int);
int pinRead(int);