#include "gpio.h"

void pinConfig(int pin, int io)
{
	if((pin>=0)&&(pin<=7))
	{
		if(io == OUTPUT)
		{
			DDRD |= (1<<pin);
		}
		
		if(io == INPUT)
		{
			DDRD &=~ (1<<pin);
		}
	}	
	
	else if ((pin>=8)&&(pin<=13))
	{
		if(io == OUTPUT)
		{
			DDRB |= (1<<(pin-8));
		}
		
		if(io == INPUT)
		{
			DDRB &=~ (1<<(pin-8));
		}
	}
}

void pinWrite(int pin, int val)
{
	if((pin>=0)&&(pin<=7))
	{
		if (val > 0)
		{
			PORTD |= (1<<pin);
		}
		
		if (val == 0)
		{
			PORTD &=~ (1<<pin);
		}
	}
	
	if ((pin>=8)&&(pin<=13))
	{
		if (val > 0)
		{
			PORTB |= (1<<(pin-8));
		}
		
		if (val == 0)
		{
			PORTB &=~ (1<<(pin-8));
		}
	}
}

int pinRead(int pin)
{
	if((pin>=0)&&(pin<=7))
	{
		return (PIND && (1<<(pin-8)));
	}
	
	else if((pin>=8)&&(pin<=13))
	{
		return (PINB && (1<<(pin-8)));
	}
	else return -1;
	
}	