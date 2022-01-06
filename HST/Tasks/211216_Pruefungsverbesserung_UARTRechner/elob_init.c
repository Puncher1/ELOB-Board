/*******************************************************************************
Firma        : GIBZ
Autor        : Robert Theiler
Projekt      : ELOB Init Routines
Version      : 1.0
Dateiname    : elob_init.c
Erstelldatum : 04.03.2021

********************************************************************************
Chip type         : ATmega2560
CPU-Clock         : 16.0000 MHz (externer Quartz)
Programm Memory   : 256 kByte
Internal RAM      : 8 kByte
EEPROM            : 4 kByte
Data Stack size   : 16 Byte

********************************************************************************
Datum             Vers.    Kommentar / Änderungsgrund
10.03.2021        1.0      Erstellung

*******************************************************************************/ 

/*------------------------------- Einbindungen -------------------------------*/
#include <avr/io.h>                 // Enthält I/O-Definitionen
#include <avr/delay.h>              // Enthält _delay_ms() und _delay_us()
#include "elob_init.h"

/*----------------------------- elob_init ------------------------------------*/
void elob_init(void)
{
	// I/O-Konfigurationen
	DDRA = 0xFF;                    // LED-Port als Ausgang definieren
	
	/***** UART INITIALISIEREN ***********************************************/
	/* Baudrate konfigurieren
	/* BAUD = F_CPU / (16 * (UBBR + 1))
	/* UBBR = F_CPU / (16 * BAUD) - 1
	/* Baudrate: 9600
	/* Konfigurationswert UBBR1 aus Datenblatt
	/**/
	UBRR1 = UART_UBBR;	
	UCSR1A = 0;							// U2Xn = 0 (Tabelle aus Datenblatt)	
	UCSR1B = 1<<TXEN1 | 1<<RXEN1;					// Transmitter Enable	
	UCSR1C = 1<<UCSZ11 | 1<<UCSZ10;		// 8 Bits
}