/*******************************************************************************
Firma        : GIBZ
Autor        :
Projekt      : Tasks
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
30.08.2021        1.0      Erstellung

*******************************************************************************/

/*------------------ Definitionen für die Delayfunktion-----------------------*/
#define F_CPU 8000000
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
void dez_to_ascii(uint16_t num);

uint16_t digit;
unsigned char writeState = 1;


/*----------------------------- Hauptprogramm --------------------------------*/

int main(void)
{
	// ELOB initialisieren (I/O und UART)
	elob_init();

	/* Lokale Variablen */
	char name[] = "Max Mustermann";
	unsigned char arrayIndex = 0;

	while(1)
	{
		
		unsigned char currentChar = name[arrayIndex];
		
		if (currentChar == 0){
			writeUART(160);
			WaitMilliseconds(1000);
			arrayIndex = 0;
		}
		else{
			writeUART(currentChar);
			arrayIndex++;
		}

	}
}

/*------------------------------- Funktionen ---------------------------------*/
void dez_to_ascii(uint16_t num){
	
	static uint16_t num_copy;
	static unsigned char digitPoint;
	
	if (digitPoint){
		writeState = 1;
		switch (digitPoint){
			case 5:
			digit = num_copy/10000;
			num_copy %= 10000;
			break;
			
			case 4:
			digit = num_copy/1000;
			num_copy %= 1000;
			break;
			
			case 3:
			digit = num_copy/100;
			num_copy %= 100;
			break;
			
			case 2:
			digit = num_copy/10;
			num_copy %= 10;
			break;
			
			case 1:
			digit = num_copy;
			break;
			
		}
		digitPoint--;
	}
	else{
		num_copy = num;
		digitPoint = numLen(num_copy);
		writeState = 0;
	}
	
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

int numLen(uint16_t n){
	if (n < 10) return 1;
	if (n < 100) return 2;
	if (n < 1000) return 3;
	if (n < 10000) return 4;
	if (n < 100000) return 5;
}