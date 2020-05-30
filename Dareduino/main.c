#include <stdio.h>

#include "scheduler.h"
#include "util.h"
#include "gpio.h"

#include <avr/io.h>
#include <avr/interrupt.h>

void onTask(void);
void offTask(void);

int main (void)
{
	init_print ();
	pinConfig(13,OUTPUT);
	
	OSinit();
	
	createTask(&onTask, 1, 50);
	createTask(&offTask, 2, 50);

	OSlaunch();
	
	return 0;
}

void onTask(void)
{
	while (1)
	{	
		printf("onTask\n");
		pinWrite(13,1);
	}
}

void offTask(void)
{
	while (1)
	{	
		printf("offTask\n");
		pinWrite(13,0);
	}
}

