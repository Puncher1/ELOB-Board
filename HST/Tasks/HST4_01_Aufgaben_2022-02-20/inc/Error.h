/**
* @file		Error.h
* @author	M.Mettler
* @date		20.02.2022
*	@brief	Error Funktion
*/

#ifndef ERROR_H_
#define ERROR_H_

/*--------------------------------- Includes ---------------------------------*/
#include <stdint.h>

/*--------------------------------- Konstanten -------------------------------*/
#define ERR_NONE           (0)
#define ERR_FIFO_FULL      (2)  // from fifo_put(uint8_t Event)
#define ERR_UART1          (5)  // UART1 error



/*---------------------------- Function Prototypes ---------------------------*/
/**
*	@brief Errorfunktion
*
* @param		ErrCode	Fehlercode
*/
void  Error(uint8_t ErrCode); 

#endif /* ERROR_H_ */