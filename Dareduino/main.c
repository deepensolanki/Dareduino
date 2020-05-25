/*
 * ArduinoPlusPlus.c
 *
 * Created: 24-05-2020 16:44:50
 * Author : Deepen
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "macros.h"

int main(void)
{
	pinConfig(13,OUTPUT);
	while(121)
	{
		pinWrite(13,1);
		_delay_ms(500);
		pinWrite(13,0);
		_delay_ms(500);
	}
}

