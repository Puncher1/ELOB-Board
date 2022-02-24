/**
* @file		elob_init.h
* @author	M.Mettler
* @date		20.02.2022
*	@brief	EloBoard Funktionen und Konfiguration
*/


#ifndef ELOB_INIT_H_
#define ELOB_INIT_H_

#define F_CPU 16000000UL
/* CPU-Clock muss vor der Einbindung von delay.h definiert werden, da dieser
		sonst bereits definiert wurde und darum nicht übernommen würde           */

/*--------------------------------- Includes ---------------------------------*/
#ifdef USE_WATCHDOG
	#include <avr/wdt.h>  // we are using the watchdog
#endif
	
#include <avr/io.h>			// I/O-Definitionen

/*--------------------------------- Makros -----------------------------------*/
// Bitmanipulationen
#define SETBIT(Adr,Bit)         (Adr |= (1<<Bit))
#define CLEARBIT(Adr,Bit)       (Adr &= ~(1<<Bit))
#define CHECKBIT(Adr,Bit)       (Adr & (1<<Bit))
#define INVERTBIT(Adr,Bit)      (Adr ^= (1<<Bit))

// I/O's definieren (LEDs, Taster und Schalter sind auf dem Elo-Board fix)
#define LEDS      PORTA
#define SCHALTER  PINC
	
/*--------------------------------- Types ------------------------------------*/
	
/*--------------------------------- Watchdog ---------------------------------*/
#ifdef USE_WATCHDOG
	#define WDT_ENABLE(t)	wdt_enable(t)       /// activate the watchdog each 60ms
	#define WDT_RESET()		wdt_reset()
#else
	#define WDT_ENABLE(t)
	#define WDT_RESET()
#endif

/*---------------------------- Function Prototypes ---------------------------*/
/**
*	@brief Initialisierung des Eloboards
*/
void elobInit(void);

#endif /* ELOB_INIT_H_ */