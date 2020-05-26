/*
 * ArduinoPlusPlus.c
 *
 * Created: 24-05-2020 16:44:50
 * Author : Deepen
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "gpio.h"
#include "macros.h"

//void TIMER1_COMPA_vect(void) __attribute__((signal));

//void scheduler();
/*
void timerInit()
{
	//Enable CTC mode by setting WGM12 bit. Set pre-scaler to 256 by setting CS12 bit
	TCCR1B |= (1<<CS12) | (1<<WGM12);
	
	//Start TCNT1 from 0
	TCNT1 = 0;
	
	//It will overflow when it reaches this compare value
	OCR1A = 30000;
	
	//Enable interrupt on match
	TIMSK1 |= (1<<OCIE1A);
	
	//Enable interrupts
	sei();
	
}
*/

int main(void)
{
	pinConfig(13,OUTPUT);
	timerInit();
	while(1);
	

	/*
	while(121)
	{
		pinWrite(13,1);
		_delay_ms(500);
		pinWrite(13,0);
		_delay_ms(500);
	}
	*/
}

/*
void taskScheduler()
{
	int a = pinRead(13);
	pinWrite(13,!a);
	printf("%s\n","In scheduler");
}
*/

/*
void TIMER1_COMPA_vect()
{
	scheduler();
}
*/
