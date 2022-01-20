/*******************************************************************************
Firma        : GIBZ
Autor        : Robert Theiler
Projekt      : ELOB Init Routines
Version      : 1.0
Dateiname    : elob_init.h
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


#ifndef ELOB_INIT_H_
#define ELOB_INIT_H_

// Defines UART
#define UART_BAUD_RATE      9600UL
#define F_CPU				16000000UL
#define UART_UBBR			((F_CPU/16UL/UART_BAUD_RATE) - 1)

// Makros
#define SETBIT(Adr,Bit)         (Adr |= (1<<Bit))
#define CLEARBIT(Adr,Bit)       (Adr &= ~(1<<Bit))
#define CHECKBIT(Adr,Bit)       (Adr & (1<<Bit))
#define INVERTBIT(Adr,Bit)      (Adr ^= (1<<Bit))

// I/O's definieren (LEDs, Taster und Schalter sind auf dem Elo-Board fix)
#define LEDS      PORTA
#define TASTER    PINJ
#define SCHALTER  PINC

// function prototypes
void elob_init(void);


#endif /* ELOB_INIT_H_ */