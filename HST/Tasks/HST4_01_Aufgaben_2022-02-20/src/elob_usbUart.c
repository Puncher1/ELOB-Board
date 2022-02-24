/**
* @file		elob_usbUart.c
* @author	M.Mettler
* @date		20.02.2022
*	@brief	EloBoard IUsb-UART UART1
*/

/*--------------------------------- Includes ---------------------------------*/
#include "elob_usbUart.h"
#include <avr/io.h>                 // I/O-Definitionen
#include <avr/interrupt.h>					// Interrupt-Definitionen
#include <stddef.h>
#include "elob_init.h"
#include "EventFifo.h"						// for event handling
#include "Error.h"

/*--------------------------------- Makros -----------------------------------*/
/* size of RX/TX buffers */
#define UART1_RX_BUFFER_MASK ( UART1_RX_BUFFER_SIZE - 1)
#define UART1_TX_BUFFER_MASK ( UART1_TX_BUFFER_SIZE - 1)

#if ( UART1_RX_BUFFER_SIZE & UART1_RX_BUFFER_MASK )
   #error RX buffer size is not a power of 2
#endif
#if ( UART1_TX_BUFFER_SIZE & UART1_TX_BUFFER_MASK )
   #error TX buffer size is not a power of 2
#endif

/*---------------------- module global variables -----------------------------*/
static volatile unsigned char UART1_TxBuf[UART1_TX_BUFFER_SIZE];
static volatile unsigned char UART1_RxBuf[UART1_RX_BUFFER_SIZE];
static volatile unsigned char UART1_TxHead;
static volatile unsigned char UART1_TxTail;
static volatile unsigned char UART1_RxHead;
static volatile unsigned char UART1_RxTail;
static volatile unsigned char UART1_LastRxError;

/*----------------------------- Interupt Functions ---------------------------*/

ISR(USART1_RX_vect)
{
	static unsigned char RxLast=0;
	unsigned char tmphead;
	unsigned char data;
	unsigned char usr;
	unsigned char lastRxError;

	// read UART status register and UART data register
	usr  = UCSR1A;
	data = UDR1;

	// get FEn (Frame Error) DORn (Data OverRun) UPEn (USART Parity Error) bits
	lastRxError = usr & ((1<<FE1)|(1<<DOR1)|(1<<UPE1) );
	
	// calculate buffer index
	tmphead = ( UART1_RxHead + 1) & UART1_RX_BUFFER_MASK;
	
	if ( tmphead == UART1_RxTail ) {
		lastRxError = UART_BUFFER_OVERFLOW >> 8; // error: receive buffer overflow
	}
	else {
		if(data == '\r' || data == '\n') {  // are data terminated by a CR or LF ?
			if(!(RxLast == '\r' || RxLast == '\n')) {
				UART1_RxHead         = tmphead;  // store new index
				UART1_RxBuf[tmphead] = 0;        // store the terminator
				eventFifoPut(EVENT_UART1_RXDATA);     // send event "rx data available"
			}
		}
		else {
			UART1_RxHead         = tmphead; // store new index
			UART1_RxBuf[tmphead] = data;   // store received data in buffer
		}
	}
	RxLast = data;  // store the actual char to check in next interrupt on CR or LF
	UART1_LastRxError |= lastRxError;

	if(UART1_LastRxError)
	Error(ERR_UART1);
}

ISR(USART1_UDRE_vect)
{
	unsigned char tmptail;
	
	if( UART1_TxHead != UART1_TxTail) {
		// calculate and store new buffer index
		tmptail = (UART1_TxTail + 1) & UART1_TX_BUFFER_MASK;
		UART1_TxTail = tmptail;
		// get one byte from buffer and write it to UART
		UDR1 = UART1_TxBuf[tmptail];  // start transmission
	}
	else {
		// tx buffer is empty -> disable UDRE interrupt
		UCSR1B &= ~(1<<UDRIE1);
	}
}


/*----------------------------- Functions ------------------------------------*/

void usbUartInit(uint16_t baudrate)
{
  /* Set baud rate */
  if ( baudrate & 0x8000 ){
	  #if U2X1
	  UCSR1A = (1<<U2X1);  //Enable 2x speed
	  #endif
  }
  UBRR1H = (uint8_t) (baudrate>>8) & 0x00FF;
  UBRR1L = (uint8_t)  baudrate & 0x00FF;

// TODO 1 Konfigurieren Sie UCSR1B und UCSR1C gemäss Datenblatt

	UCSR1B = 0x98;			// Rx Complete Interrupt En, Transmitter En, Reciever En
	UCSR1C = 0x06;								// 8 Bits
	
		
  sei();                 // and allow all interrupts now
}

void usbUartPutC(const char data)
{
	unsigned char tmphead;
	tmphead  = (UART1_TxHead + 1) & UART1_TX_BUFFER_MASK;
	
	while ( tmphead == UART1_TxTail ) {  // is the tx buffer full?
		;// wait until ready to send
	}
	
	UART1_TxBuf[tmphead] = data;
	UART1_TxHead = tmphead;

	// enable UDRE interrupt
	UCSR1B    |= (1<<UDRIE1);

}

void usbUartPutS(const char *text )
{
	while (*text)
	usbUartPutC(*text++);

}

uint16_t usbUartGetC(void)
{
	uint8_t tmptail;
	uint16_t  data;
	uint8_t lastRxError;

	if ( UART1_RxHead == UART1_RxTail ) {
		return UART_NO_DATA;   // no data available
	}
	
	// calculate buffer index
	tmptail = (UART1_RxTail + 1) & UART1_RX_BUFFER_MASK;
	
	// get data from receive buffer
	data = UART1_RxBuf[tmptail];
	lastRxError = UART1_LastRxError;
	
	// store buffer index
	UART1_RxTail = tmptail;
	
	UART1_LastRxError = 0;
	return (lastRxError << 8) + data;

}

uint8_t usbUartGetRxBuffer(char* pDest, uint8_t DestSize)
{
	uint8_t  c, CharCnt = 0;
	uint16_t Err;

	if(pDest != NULL) {												// continue only on a valid pointer
		while( (Err = usbUartGetC()) < 0xff) {		// get a char from the uart fifo
			*pDest = c = Err & 0xff;							// store them
			++pDest;
			if(c == 0)														// is the buffer at the end
			return CharCnt;												// yes -> finished
			++CharCnt;													  // next char
		}
	}
	return 0; // error or no data received
}