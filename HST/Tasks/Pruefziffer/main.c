/*
 * Pruefziffer Auslesen
 *
 * Author: Andrin Schaller
 * ********************************
 * Date			Vers.	Name				Comment / Change
 * 06.01.2022	1.0		Andrin Schaller		Creation
 */


// *** INCLUDES ***
#include <avr/io.h>
#include "elob_init.h"

// *** DEFINES ***


// *** STRUCTURES ***


// *** GLOBAL ***
uint8_t readUART();
int CalcPruefziffer(const int * aArrayP);
void writeUART(uint8_t zeichen);

/*
 * MAIN-ROUTINE
 */
int main(void){
	
	// *** INITIALIZATION ***
	
	elob_init();
	// ** I/O **
	
	// ** Local Variables **
	uint8_t tReadIndex = 0;
	
	uint8_t tCharFromUART;
	int tNumFromUART[10] = { 0 };
	int tCheckNum;
	
	// ** Interrupts **
	

	// *** PROGRAM-LOOP ***
	while (1){
		if (tReadIndex > 9)
		{
			tReadIndex = 0;
			tCheckNum = CalcPruefziffer(&tNumFromUART);
			writeUART(tCheckNum + 48);
			
			for (int i = 0; i < 100; ++i)
			{
				tNumFromUART[i] = 0;
			}
		}
		else
		{
			tCharFromUART = readUART();
			tNumFromUART[tReadIndex] = tCharFromUART - 48;
			
			// TODO
			tReadIndex++;
		}
	}
}


// *** FUNCTIONS ***


/*
 * @brief: Writes data from UART interface 
 * @return: 8-bit char from UART interface
 */
uint8_t readUART(){
	
	while ((UCSR1A & (1<<RXC1)) == 0);
	return UDR1;
	
}

void writeUART(uint8_t zeichen)
{
	while ((UCSR1A & (1<<UDRE1)) == 0);	// warten bis Senderegister leer ist
	UDR1 = zeichen;						// Zeichen senden
}

int CalcPruefziffer(const int * aArrayP)
{
	int tSumOddNums = 0;
	int tSumEvenNums = 0;
	int tSumOfSums;
	int tRemainOfSum;
	uint8_t tNumPos = 10;
	
	for (uint8_t tArrayIndex = 0; tArrayIndex < 9; tArrayIndex++)
	{
		if ((tNumPos % 2) == 0)
		{
			tSumEvenNums += aArrayP[tArrayIndex];
		}
		else
		{
			tSumOddNums += aArrayP[tArrayIndex];
		}
		
		tNumPos--;
	}
	
	tSumEvenNums *= 3;
	tSumOfSums = tSumOddNums + tSumEvenNums;
	tRemainOfSum = tSumOfSums % 10;
	
	if (tRemainOfSum > 0)
	{
		tRemainOfSum = 10 - tRemainOfSum;
	}
	
	return tRemainOfSum;
}