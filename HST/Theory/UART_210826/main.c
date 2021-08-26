/*******************************************************************************
Firma        : GIBZ
Autor        : Vorname Name
Projekt      : Vorlagenprojekt
Version      : 1.0
Dateiname    : main.c
Erstelldatum : 07.10.2020

********************************************************************************
Chip type         : ATmega2560
CPU-Clock         : 16.0000 MHz (externer Quartz)
Programm Memory   : 256 kByte
Internal RAM      : 8 kByte
EEPROM            : 4 kByte
Data Stack size   : 16 Byte

********************************************************************************
Datum             Vers.    Kommentar / Änderungsgrund
06.04.2018        1.0      Erstellung

*******************************************************************************/

/*------------------ Definitionen für die Delayfunktion-----------------------*/
#define F_CPU 16000000UL
/* CPU-Clock muss vor der Einbindung von delay.h definiert werden, da dieser
   sonst bereits definiert wurde und darum nicht übernommen würde             */

/*------------------------------- Einbindungen -------------------------------*/
#include <avr/io.h>                 // Enthält I/O-Definitionen
#include <avr/delay.h>              // Enthält _delay_ms() und _delay_us()
#include "elob_init.h"

/*---------------------------- Globale Variablen -----------------------------*/
char FlankeTastePos;
/*--------------------- Konstanten & Definitionen ----------------------------*/

// Konstanten

// Makros
#define SETBIT(Adr,Bit)         (Adr |= (1<<Bit))
#define CLEARBIT(Adr,Bit)       (Adr &= ~(1<<Bit))
#define CHECKBIT(Adr,Bit)       (Adr & (1<<Bit))
#define INVERTBIT(Adr,Bit)      (Adr ^= (1<<Bit))


// I/O's definieren (LEDs, Taster und Schalter sind auf dem Elo-Board fix)
#define LEDS      PORTA
#define TASTER    PINJ
#define SCHALTER  PINC

/*--------------------------- Funktionsprototypen ----------------------------*/
void WaitMilliseconds(int MilliSeconds);
void PosFlankenerkennung(void);
void writeUART(uint8_t zeichen);

/*----------------------------- Hauptprogramm --------------------------------*/

int main(void)
{
  // ELOB initialisieren (I/O und UART)
  elob_init();

  while(1)
  {
    
  }                               
}

/*------------------------------- Funktionen ---------------------------------*/
void writeUART(uint8_t zeichen)
{
	while ((UCSR1A & (1<<UDRE1)) == 0);	// warten bis Senderegister leer ist
	UDR1 = zeichen;						// Zeichen senden
}

void WaitMilliseconds(int MilliSeconds)
{
  for(int i = 0; i < MilliSeconds; i++)
  {
    _delay_ms(1);
  }  
}

void PosFlankenerkennung(void)
{
	static char TastenVorher = 0;
	char TastenAktuell;
	TastenAktuell = TASTER;
	FlankeTastePos = TastenAktuell & ~TastenVorher;
	TastenVorher = TastenAktuell;
}