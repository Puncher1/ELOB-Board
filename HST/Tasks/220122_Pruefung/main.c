/*
 * Prüfung vom 20.01.2021
 *
 * Author: Andrin Schaller
 * ********************************
 * Date			Vers.	Name				Comment / Change
 * 20.01.2022	1.0		Andrin Schaller		Creation
 */


// *** INCLUDES ***
#include <avr/io.h>
#include "elob_init.h"

// *** DEFINES ***


// *** STRUCTURES ***


// *** GLOBAL ***
int8_t input(uint8_t* pZahl);
uint8_t readUART();
void writeUART(uint8_t something);

/*
 * MAIN-ROUTINE
 */
int main(void){
	
	// *** INITIALIZATION ***
	elob_init();
	
	// ** I/O **
	
	// ** Local Variables **
	uint8_t tNum[100];
	int tIndex = 0;
	int tWriteIndex = 0;
	char tERRMsg[3] = "ERR";
	
	// ** Interrupts **
	

	// *** PROGRAM-LOOP ***
	while (1){
		
		uint8_t tChar = readUART();
		
		if (tChar == 13)
		{
			int8_t tStateOfInput= input(&tNum);
			if (tStateOfInput == -2 || tStateOfInput == -1)
			{
				for (tWriteIndex; tWriteIndex < 3; tWriteIndex++)
				{
					writeUART(tERRMsg[tWriteIndex]);
				}
				tWriteIndex = 0;
			}
			
			for (int i = 0; i < 100; ++i)
			{
				tNum[i] = 0;
			}
			tIndex = 0;
		}
		else
		{
			tNum[tIndex] = tChar;
		}
		tIndex++;
		
	}
}


// *** FUNCTIONS ***

int8_t input(uint8_t* pZahl)
{
	int tFacIndex = 0;
	int tWriteIndex = 0;
	int tFinalResultIndex = 0;
	int tLenghtOfArray = sizeof(pZahl) / sizeof(pZahl[0]) - 1;
	int tLenght = pZahl[0] - 48 - 1;		// -1: for the for loop
	int tCurrentNum = 1;
	int tFinalResult = 1;
	char tFinalArray[100];
	
	if (tLenghtOfArray > 1)
	{
		return -2;
	}
	else if ((pZahl[0] - 48) > 5)
	{
		return -2;
	}
	
	for (tFacIndex; tFacIndex < tLenght; tFacIndex++)
	{
		tFinalResult *= tCurrentNum + 1;
		tCurrentNum++;
	}
	
	
	while (tFinalResult > 0) {
		int d = tFinalResult % 10;
		tFinalArray[tFinalResultIndex] = d + 48;
		
		tFinalResult /= 10;
		tFinalResultIndex++;
	}
	
	
	
	while (tFinalArray[tWriteIndex] != 0)
	{
		writeUART(tFinalArray[tWriteIndex]);
		tWriteIndex++;
	}
	
	
	for (int i = 0; i < 100; ++i)
	{
		tFinalArray[i] = 0;
	}
	return 0;	
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