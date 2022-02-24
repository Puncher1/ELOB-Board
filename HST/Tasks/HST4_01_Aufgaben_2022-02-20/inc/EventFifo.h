/**
* @file		EventFifo.h
* @author	M.Mettler
* @date		20.02.2022
*	@brief	Event Fifo Buffer
*/

#ifndef EVENTFIFO_H
#define  EVENTFIFO_H

/*--------------------------------- Includes ---------------------------------*/
#include <avr/io.h>                 //  I/O-Definitionen

/*--------------------------------- Konstanten -------------------------------*/
#define  FIFO_SIZE  8								//  uint8_t the total length of the circular buffer in bytes

/*--------------------------- Queue Event definitions ------------------------*/
	
#define EVENT_UART1_RXDATA  (6)			// the uart has data available
#define EVENT_SPI_RXDATA		(7)  // the spi has data available

/*---------------------------- Function Prototypes ---------------------------*/

/**
*	@brief Initialisierung des FiFo
*/
extern void eventFifoInit(void);

/**
*	@brief Element hinzufügen
*	@param	Event	Neues Element
*/
extern void eventFifoPut(uint8_t Event);

/**
*	@brief Element herausnehmen
*
*	@return	letztes Element
*/
extern uint8_t eventFifoGet(void);

#endif
