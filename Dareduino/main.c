#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

#include "scheduler.h"
#include "util.h"
#include "gpio.h"

void onTask(void);
void offTask(void);
void rTask(void);
void qTask(void);

int main (void)
{
	consoleDisplay();
	pinConfig(13,OUTPUT);
	
	OSinit();
	
	createTask(&onTask, 20, 50, "onTask");
	createTask(&rTask, 1, 50, "rTask");
	createTask(&qTask, 12, 50, "qTask");
	createTask(&offTask, 2, 50, "offTask");

	OSlaunch(PRIORITYBASED);

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

void rTask()
{
	while (1)
	{
		printf("rTask\n");
	}	
}

void qTask()
{
	while (1)
	{
		printf("qTask\n");
	}
}
