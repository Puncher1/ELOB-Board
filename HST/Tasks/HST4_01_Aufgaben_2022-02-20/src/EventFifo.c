/**
* @file		EventFifo.c
* @author	M.Mettler
* @date		20.02.2022
*	@brief	Event Fifo Buffer
*/
   
/*--------------------------------- Includes ---------------------------------*/
#include "EventFifo.h"
#include "Error.h"

/*--------------------------------- Makros -----------------------------------*/
#define FIFO_MASK ( FIFO_SIZE - 1)

#if ( FIFO_SIZE & FIFO_MASK )
   #error FIFO size is not a power of 2
#endif

/*---------------------- module global variables -----------------------------*/
static volatile uint8_t  fifo_Queue[FIFO_SIZE];
static volatile uint8_t  fifo_Head;
static volatile uint8_t  fifo_Tail;


/*----------------------------- Functions ------------------------------------*/

void eventFifoInit(void)
{
   //memset((void*)fifo_Queue, 0, FIFO_SIZE); // braucht es nicht, da Head und Tail richtig arbeiten sollten
   fifo_Head = fifo_Tail = 0;
}


void eventFifoPut(uint8_t Event)
{
   // calculate buffer index
   register uint8_t tmphead = ( fifo_Head + 1) & FIFO_MASK;

   if ( tmphead == fifo_Tail ) {  // buffer full?
      Error(ERR_FIFO_FULL);
   }
   else {
      fifo_Head         = tmphead;  // update the new head
      fifo_Queue[tmphead] = Event;  // and append the event into the buffer
   }
}


uint8_t eventFifoGet(void)
{
   register uint8_t  tmptail;
   register uint8_t  Event;

   if ( fifo_Head == fifo_Tail ) 
      return 0;   // no data available
    
   // calculate buffer index
   tmptail = (fifo_Tail + 1) & FIFO_MASK;
    
   // get data from the queue buffer
   Event = fifo_Queue[tmptail];
    
   fifo_Tail = tmptail;  // update the tail now
    
   return Event;
}

