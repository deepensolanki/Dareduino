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

uint8_t *semaphore;		

taskTCB *head, *runPt, *tempPt;
taskTCB *newTask, *t;

void TIMER1_COMPA_vect (void) __attribute__ ((signal,naked));
void taskScheduler(void) __attribute__((naked));

void swapNodes(taskTCB *a, taskTCB *b)
{	
	t->fnPtr = a->fnPtr;
	t->id = a->id;
	t->neverRun = a->neverRun;
	t->priority = a->priority;
	t->sP = a->sP;
	t->status = a->status;
	
	a->fnPtr = b->fnPtr;
	a->id = b->id;
	a->neverRun = b->neverRun;
	a->priority = b->priority;
	a->sP = b->sP;
	a->status = b->status;
	
	b->fnPtr = t->fnPtr;
	b->id = t->id;
	b->neverRun = t->neverRun;
	b->priority = t->priority;
	b->sP = t->sP;
	b->status = t->status;	
	
}

void sortTaskList()
{
	taskTCB *temp1;
	taskTCB *temp2;

	for(temp1=head->next; temp1!=NULL; temp1=temp1->next)
	{
		for(temp2=temp1->next; temp2!=NULL; temp2=temp2->next)
		{
			if(temp2->priority < temp1->priority)
			{
				swapNodes(temp1, temp2);
			}
		}
	}
}

void timerInit(void) 
{
    TCCR1B |= (1<<WGM12) | (1<<CS12);
    TIMSK1 |= ( 1 << OCIE1A );
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
  if(schType == PRIORITYBASED)
	sortTaskList();
  printf("Starting scheduler with %d tasks", tasksCreated);
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

    asm volatile("ret");	
}
