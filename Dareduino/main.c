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
	
	sem = 2;
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
		OSwait(semaphore);
		printf("\nOnTask %d", (*semaphore));
		pinWrite(13,1);
		OSsignal(semaphore);
		printf("\nOnTask %d", (*semaphore));
	}
}

void offTask(void)
{
	while (1)
	{
		OSwait(semaphore);
		printf("\nOffTask %d", (*semaphore));
		printf("\nOfftask");
		pinWrite(13,0);
		OSsignal(semaphore);
		printf("\nOffTask %d", (*semaphore));
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
	while (1)
	{
		printf("\nqTask");
	}
}