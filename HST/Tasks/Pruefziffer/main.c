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
			
			
		}
		else
		{
			tCharFromUART = readUART();
			tNumFromUART = tNumFromUART[tReadIndex - 48];
			
			tCheckNum = CalcPruefziffer(&tNumFromUART);
			
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
	
	if (tRemainOfSum != 0)
	{
		tSumOfSums - 10;
	}
	
	return tSumOfSums;
}