/*
 * adc.c
 *
 * Created: 06-06-2020 12:44:31
 *  Author: Deepen
 */ 

#include "adc.h"
#include <avr/io.h>
#include <util/delay.h>

void adcInit()
{
	ADCSRA = 0x87;
	ADMUX = 0x40;
}

int adcRead(int channel)
{
	int aHigh, aLow;
	ADMUX = ADMUX | (channel & 0x0f);
	ADCSRA |= (1<<ADSC);
	while((ADCSRA & (1<<ADIF)) == 0);
	_delay_us(10);
	aLow = (int) ADCL;
	aHigh = (int)ADCH*256;
	aHigh = aLow + aHigh;
	return aHigh;
}
