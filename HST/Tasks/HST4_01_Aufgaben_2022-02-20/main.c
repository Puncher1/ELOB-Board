/**
* @file		main.cpp
* @author	M.Mettler
* @date		20.02.2022
*	@brief	Main Programm
*	@version	2022-02-20 Minimalprojekt
*/

/*--------------------------------- Includes ---------------------------------*/
#include "elob_init.h"
#include "EventFifo.h"
#include "elob_usbUart.h"
#include <avr/io.h>                 // I/O-Definitionen
#include <string.h>
#include <avr/interrupt.h>					// Interrupts
#include <stdlib.h>

/*---------------------- ------ global types ---------------------------------*/
typedef enum {eStateInit,
			  eStateIdle,
			  eStateError,
			  eStateInvalidCommand,
			  eStatePrintHello,
			  eStatePrintName,
			  eStateUART1RxData,
}EState;
	
/*---------------------- ------ global variables -----------------------------*/
uint8_t Event;								// not necessarily as a global variable, but easier to debug
EState	state = eStateInit;

/*--------------------------------- Konstanten -------------------------------*/
	
/*----------------------------- Interupt Functions ---------------------------*/

/*-------------------------------------- Functions ---------------------------*/


/*----------------------------- Hauptprogramm --------------------------------*/
int main(void)
{
	// Variablen für RS232
	char RxBuffer[UART1_RX_BUFFER_SIZE], TxBuffer[UART1_TX_BUFFER_SIZE];
	
	
	while(1)	//SuperLoop
	{			
		// Statemachine
		switch(state) {
			case eStateInit:
				elobInit();								// initialize EloBoard
				eventFifoInit();					    // initialize the event queue
				usbUartInit(UART_BAUD_SELECT(115200UL ,F_CPU));	// UART init
				usbUartPutS("\nBoard Initialized\n");
				
				WDT_ENABLE(WDTO_2S); // activate the watchdog if USE_WATCHDOG defined
				
				state = eStateIdle;
				break;
				
			case eStateIdle:
				// Auswertung der Queue
				if((Event = eventFifoGet())) {		// Event Queue abfragen
					switch(Event) {
						case EVENT_UART1_RXDATA:			// Zeichen von UART empfangen
							state = eStateUART1RxData;
							break;
					}
				}
				break;
				
			case eStateUART1RxData:
				usbUartGetRxBuffer(RxBuffer, sizeof(RxBuffer));	// UART auslesen
				// Befehle auswerten
				if (strcmp(RxBuffer,"HELLO") == 0) {		
					state = eStatePrintHello;
				}
				else if (strcmp(RxBuffer, "NAME") == 0)
				{
					state = eStatePrintName;
				}
				else{
					state = eStateInvalidCommand;
				}
				break;
				
			case eStatePrintHello:
				usbUartPutS("Hello World\n");
				state = eStateIdle;
				break;
			
			case eStatePrintName:
				usbUartPutS("Andrin Schaller\n");
				state = eStateIdle;
				break;
							
			case eStateInvalidCommand:
				usbUartPutS("\"");
				usbUartPutS(RxBuffer);
				usbUartPutS("\" is not a valid Command\n");
				state = eStateIdle;
				break;
								
			case eStateError:
				;
				break;
		}
		
		WDT_RESET();     // necessary because watch dog is switched on	
	}	                         
}

