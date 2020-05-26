/*
 * Dareduino.c
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

int main(void)
{
	pinConfig(13,OUTPUT);
	timerInit();
	while(1);
}

