#include <stdio.h>

#include "scheduler.h"
#include "util.h"
#include "gpio.h"

#include <avr/io.h>
#include <avr/interrupt.h>

void function_1(void);
void function_2(void);
void function_3(void);
void function_4(void);

void int0_init (void)
{
	DDRD &= ~( 1 << DDD2 ); //PD2 is an input
	PORTD |= ( 1 << PORTD2 ); //turn on pullup

	EICRA |= ( 0 << ISC00 );
	EICRA |= ( 1 << ISC01 );

	EIMSK |= ( 1 << INT0 ); //turn on INT0
}

void INT0_vect ( void ) __attribute__ ( ( signal ) );

void INT0_vect ( void )
{
	cli ();
	printf ("Interrupt triggered\n");
	sei ();
}

int main ( void )
{
	init_print ();
	int0_init ();
	
	OSinit();
	
	createTask(&function_1, 1, 200);
	createTask(&function_2, 2, 200);
	createTask(&function_3, 3, 200);
	createTask(&function_4, 4, 50);

	OSlaunch();
	
	return 0;
}

void function_1 ( void )
{
	while (1)
	{	
		printf ( "Function 1\n" );
	}
}

void function_2 ( void )
{
	while (1)
	{	
		printf ( "Function 2\n" );
	}
}

void function_3 ( void )
{
	while (1)
	{
		printf ( "Function 3\n" );
		
	}
}

void function_4 ( void )
{
	
	while (1)
	{
		printf ( "Function 4" );
		
	}
}
