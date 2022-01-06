/*
 * Pruefungsverbesserung UART Rechner (Pruefung vom 9.12.21)
 *
 * Author: Andrin Schaller
 * ********************************
 * Date			Vers.	Name				Comment / Change
 * 16.21.2021	1.0		Andrin Schaller		Creation
 */


// *** INCLUDES ***
#include <avr/io.h>
#include "elob_init.h"

// *** DEFINES ***


// *** STRUCTURES ***


// *** GLOBAL ***
int8_t ReceiveNumber(float * pNumber);
uint8_t readUART();

/*
 * MAIN-ROUTINE
 */
int main(void){
	
	// *** INITIALIZATION ***
	
	// ** I/O **
	
	// ** Local Variables **
	float number;
	
	
	// ** Interrupts **
	

	// *** PROGRAM-LOOP ***
	while (1){
		int8_t state = ReceiveNumber(&number);
	}
}


// *** FUNCTIONS ***

/************************************************************************/
/* Liest Zahl von UART.
 * Liest Zahl im Format xxx.y aus.
 * @param pNumber: Der Pointer auf die Variable, in der die Zahl abgespeichert werden soll.
 * @return: 0= okay, -1= error
/************************************************************************/
int8_t ReceiveNumber(float * pNumber)
{
	float number = 0;
	float ziffer;
	char punkt;
	
	for (unsigned char i = 0; i<=3; i++)
	{
		ziffer = readUART();
		ziffer -= 48;
		if (ziffer < 10 && ziffer >= 0)
		{
			number *= 10;
			number += ziffer;
		}
		else
		{
			return -1;
		}
	}
	punkt = readUART();
	if (punkt != '.')
	{
		return -1;
	}
	ziffer = readUART();
	ziffer -= 48;
	
	if (ziffer < 10 && ziffer >= 0)
	{
		ziffer /= 10;
		number += ziffer;
		
		*pNumber = number;
		return 0;
	}
	else
	{
		return -1;
	}
	
}

/*
 * @brief: Writes something to the UART interface
 * @params:
 *		something: Something that gets written to UART interface
 */
void writeUART(uint8_t something)
{
	while ((UCSR1A & (1<<UDRE1)) == 0);		// wait until send-register is empty
	UDR1 = something;						// sending
}

/*
 * @brief: Reads from the UART interface
 * @return: The input of the UART interface
 */
uint8_t readUART(){
	
	while ((UCSR1A & (1<<RXC1)) == 0);		
	return UDR1;
		
}
