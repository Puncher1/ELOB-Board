/**
* @file		elob_usbUart.c
* @author	M.Mettler
* @date		20.02.2022
*	@brief	EloBoard IUsb-UART UART1
*/


#ifndef ELOB_USBUART_H_
#define ELOB_USBUART_H_

/*--------------------------------- Includes ---------------------------------*/
#include "elob_init.h"
#include <avr/io.h>                 //  I/O-Definitionen

/*--------------------------------- Konstanten -------------------------------*/
#define UART1_RX_BUFFER_SIZE 128
#define UART1_TX_BUFFER_SIZE 32

/* test if the size of the circular buffers fits into SRAM */
#if ( (UART1_RX_BUFFER_SIZE+UART1_TX_BUFFER_SIZE) >= (RAMEND-0x60 ) )
	#error "size of UART1_RX_BUFFER_SIZE + UART1_TX_BUFFER_SIZE larger than size of SRAM"
#endif

/*  high byte error return code of uart_getc() */
#define UART_BUFFER_OVERFLOW  0x0200              /**< @brief receive ring buffer overflow */
#define UART_NO_DATA          0x0100              /**< @brief no receive data available    */
	
/*--------------------------------- Makros -----------------------------------*/
#define UART_BAUD_SELECT(baudRate,xtalCpu)  (((xtalCpu) + 8UL * (baudRate)) / (16UL * (baudRate)) -1UL)

/*---------------------------- Function Prototypes ---------------------------*/
/**
*	@brief Initialisierung der UART
*
* @param baudrate	Baudrate der UART
*/
void usbUartInit(uint16_t baudrate);

/**
*	@brief Write Char to Uart
*
* @param data	byte to be transmitted
*/
void usbUartPutC(char zeichen);

/**
*	@brief Transmit string to UART1
*
* @param	text	string to be transmitted
*/
void usbUartPutS(const char *text);

/**
*	@brief Get Char from UART
*
* @return		lower byte:  received byte from ringbuffer
*						higher byte: last receive error
*/
uint16_t usbUartGetC(void);

/**
* @brief    Gets the RX Buffer content
*
* @param    pDest The destination memory for the received data
* @param    DestSize  The maximum size of the destination memory
* @return   The number of characters received
*/
uint8_t usbUartGetRxBuffer(char* pDest, uint8_t DestSize);

#endif /* ELOB_USBUART_H_ */