/*
 * DESCRIPTION
 *
 * Author: Puncher1
 * ********************************
 * Date			Vers.	Name				Comment / Change
 * 24.08.2021	1.0		Puncher1			Creation
 */


// *** INCLUDES ***
#include <avr/io.h>

// *** DEFINES ***


// *** STRUCTURES ***


// *** GLOBAL ***


/*
 * MAIN-ROUTINE
 */
int main(void){
	
	// *** INITIALIZATION ***
	
	// ** I/O **
	
	// ** Local Variables **
	
	// ** Interrupts **
	
	// ** UART **
	elob_init();

	// *** PROGRAM-LOOP ***
	while (1){
		
	}
}


// *** FUNCTIONS ***

void writeUART(uint8_t zeichen)
{
	while ((UCSR1A & (1<<UDRE1)) == 0);	// warten bis Senderegister leer ist
	UDR1 = zeichen;						// Zeichen senden
}