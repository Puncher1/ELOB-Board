/**
* @file		Error.c
* @author	M.Mettler
* @date		20.02.2022
*	@brief	Error Funktion
*/

 
/*--------------------------------- Includes ---------------------------------*/
#include "Error.h"
#include "elob_init.h"

/*----------------------------- Functions ------------------------------------*/

void Error(uint8_t ErrCode)
{
	uint8_t newError = ErrCode;
	ErrCode = newError;
  while(1)        // loop for ever to 
    WDT_RESET();
}