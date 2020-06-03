#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <util/delay.h>

#include "scheduler.h"

uint16_t stackUsed;
uint16_t mainSp;
uint16_t *currSp;

uint8_t tasksCreated, schedulerType;

taskTCB *head, *runPt, *tempPt;
taskTCB *newTask, *t;

void TIMER1_COMPA_vect (void) __attribute__ ((signal,naked));
void taskScheduler(void) __attribute__((naked));

void timerInit(void)
{
	TCCR1B |= (1<<WGM12) | (1<<CS12);
	TIMSK1 |= (1 << OCIE1A);
	OCR1A = 61500;
}

void TIMER1_COMPA_vect ( void )
{
	saveContext();
	taskScheduler();
	currSp = &(runPt->sP);
	loadStackPointer();
	
	if(runPt->neverRun == TRUE)
	{
		sei();
		runPt->neverRun = FALSE;
		runPt->fnPtr();
	}
	else
	{
		restoreContext();
		asm volatile ("reti");
	}
}

void OSinit(void)
{
	cli();
	timerInit();
	head->next = NULL;
	head->status = HEAD;
	runPt = head;
	stackUsed = 0;
	tasksCreated = 0;
}

void OSlaunch(uint8_t schType)
{
	currSp = &mainSp;
	schedulerType = schType;
	printf("Starting scheduler with %d tasks\n", tasksCreated);
	_delay_ms(2000);
	sei();
	while(1)
	{
		printf("Scheduler running\n");
	}
	
}

void createTask(void(*fPtr)(void), uint8_t priority, uint16_t stack_size, char *name)
{
	tasksCreated += 1;
	newTask = (taskTCB *)malloc(sizeof(taskTCB));
	newTask->fnPtr = fPtr;
	newTask->priority = priority;
	newTask->neverRun = TRUE;
	newTask->status = READY;
	newTask->sP = USER_STACK_SPACE - stackUsed;
	stackUsed += stack_size;
	newTask->id = name;
	newTask->blocked = NULL;
	
	newTask->next = head->next;
	head->next = newTask;
}

void taskScheduler(void)
{
	if(runPt->status == HEAD)
	{
		runPt = runPt->next;

	}
	else if(runPt->next == NULL)
	{
		runPt = head->next;
	}
	else
	{
		runPt = runPt->next;
	}
	
	while(runPt->blocked != NULL)
		runPt = runPt->next;
	
	asm volatile("ret");
}

void OSsuspend(void)
{
	TIMER1_COMPA_vect();
}

void OSwait(volatile int *s)
{
	cli();
	(*s)--;
	if((*s) < 0)
	{
		runPt->blocked = s;
		sei();
		OSsuspend();
	}
	sei();
}

void OSsignal(volatile int *s)
{
	taskTCB *temp;
	cli();
	(*s)++;
	if((*s) < 0)
	{
		temp = runPt->next;
		while(temp->blocked != s)
		{
			temp = temp->next;
		}
		temp->blocked = NULL;
	}
	sei();
}
