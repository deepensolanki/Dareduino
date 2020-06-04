#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "scheduler.h"
#include "util.h"
#include "gpio.h"

void onTask(void);
void offTask(void);
void rTask(void);
void qTask(void);

volatile int *semaphore;
volatile int sem;

int main (void)
{
	consoleDisplay();
	pinConfig(13,OUTPUT);
	
	sem = 1;
	semaphore = &sem;
	
	OSinit();
	
	createTask(&onTask, 20, 150, "onTask");
	createTask(&rTask, 1, 150, "rTask");
	createTask(&qTask, 12, 150, "qTask");
	createTask(&offTask, 2, 150, "offTask");

	OSlaunch(ROUNDROBIN);

	return 0;
}

void onTask(void)
{

	while (1)
	{
		pinWrite(13,1);
		printf("\nOnTask");
	}
}

void offTask(void)
{
	static int i = 0;
	int y;
	while (1)
	{
		y = FIFOput(i);
		printf("\nOfftask %d", y);
		i += 1;
		pinWrite(13,0);
	}
}

void rTask()
{
	while (1)
	{
		printf("\nrTask");
	}
}

void qTask()
{
	int x;
	while (1)
	{
		x = FIFOget();
		printf("\nqTask %d", x);
	}
}