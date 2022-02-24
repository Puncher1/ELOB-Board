/**
* @file		elob_init.c
* @author	M.Mettler
* @date		20.02.2022
*	@brief	EloBoard Funktionen und Konfiguration
*/

/*--------------------------------- Includes ---------------------------------*/
#include "elob_init.h"
#include <avr/io.h>                 // I/O-Definitionen


/*----------------------------- Functions ------------------------------------*/
void elobInit(void)
{
	// I/O-Konfigurationen
	DDRA = 0xFF;                    // LED-Port als Ausgang definieren
	
}