#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <avr/sleep.h>

#include "scheduler.h"

uint16_t stackUsed;
uint16_t mainSp;
uint16_t *currSp;


taskTCB *head, *runPt;
taskTCB *newTask;

void TIMER1_COMPA_vect (void) __attribute__ ((signal,naked));
void taskScheduler(void) __attribute__((naked));

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
}

void OSlaunch(void)
{
  currSp = &mainSp;
  sei();
  while(1)
  {
	  printf("Scheduler running\n");
  }
}

void createTask(void(*fPtr)(void), uint8_t priority, uint16_t stack_size)
{ 
  newTask = (taskTCB *)malloc(sizeof(taskTCB));
  newTask->fnPtr = fPtr;
  newTask->priority = priority;
  newTask->neverRun = TRUE;
  newTask->status = RUN;
  newTask->sP = USER_STACK_SPACE - stackUsed;
  stackUsed += stack_size;
  
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
