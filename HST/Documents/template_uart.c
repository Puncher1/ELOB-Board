/*
 * DESCRIPTION
 *
 * Author: Andrin Schaller
 * ********************************
 * Date			Vers.	Name				Comment / Change
 * 24.08.2021	1.0		Andrin Schaller		Creation
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
	
	/* ** UART **
	 * Configurate baudrate
	 * BAUD = F_CPU / (16 * (UBBR + 1))
	 * UBBR = F_CPU / (16 * BAUD) - 1
	 * Baudrate: 9600
	 * Config value UBBR1 out of datasheet
	*/
	UBRR1 = UART_UBBR;	
	UCSR1A = 0;							// U2Xn = 0 (Table out of datasheet)	
	UCSR1B = 1<<TXEN1;					// Transmitter enable	
	UCSR1C = 1<<UCSZ11 | 1<<UCSZ10;		// 8 bits

	// ** I/O **
	
	// ** Interrupts **

	// ** Local Variables **
	
	
	// *** PROGRAM-LOOP ***
	while (1){
		
	}
}


// *** FUNCTIONS ***

/*
 * @brief: Writes something the UART interface
 * @params:
 *		something: Something that gets written to UART interface
 */
void writeUART(uint8_t something)
{
	while ((UCSR1A & (1<<UDRE1)) == 0);	// wait until send-register is empty
	UDR1 = something;						// sending
}