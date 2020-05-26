/*
 * scheduler.c
 *
 * Created: 26-05-2020 17:46:19
 *  Author: Deepen
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "scheduler.h"
#include "gpio.h"

void TIMER1_COMPA_vect(void) __attribute__((signal));

void timerInit()
{
	//Enable CTC mode by setting WGM12 bit. Set pre-scaler to 256 by setting CS12 bit
	TCCR1B |= (1<<CS12) | (1<<WGM12);
	
	//Start TCNT1 from 0
	TCNT1 = 0;
	
	//It will overflow when it reaches this compare value
	OCR1A = 31250; 
	
	//Enable interrupt on match
	TIMSK1 |= (1<<OCIE1A);
	
	//Enable interrupts
	sei();
	
}

void taskScheduler()
{
	int a = pinRead(13);
	pinWrite(13,!a);
}

void TIMER1_COMPA_vect()
{
	taskScheduler();
}