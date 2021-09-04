/*
 * LauflichtVariabel.c
 *
 * Created: 23.08.2021
 * Author : Puncher1
 *
 * Description:
 * Bei Programmstart soll die LED ganz rechts leuchten. 
 * Bei Betätigung der Taste „StartStopp“ soll die leuchtende LED im 1Hz-Takt beginnen nach links zu laufen. 
 * Mit erneuter Betätigung der Taste „StartStopp“ soll die leuchtende LED jeweils anhalten, respektive weiterlaufen. 
 * Erreicht die leuchtende LED das eine Ende, soll sie auf der anderen Seite wiedererscheinen und in dieselbe Richtung weiterlaufen. 
 * Mittels Taste „RichtungAendern“ soll die Laufrichtung der leuchtenden LED geändert werden. 
 * Über die Tasten „Schneller“ und „Langsamer“ soll die Geschwindigkeit des Lauflichts erhöht und verringert werden – 
 * wähle ein sinnvolles Minimum/Maximum nach eigenem Gutdünken…
 *
 */ 

#include <avr/io.h>

#define F_CPU 8000000
#include <util/delay.h>

#define tstStartStopp			(pinj_pos & (1<<0))
#define tstChangeDir			(pinj_pos & (1<<1))
#define tstSpeedUp				(pinj_pos & (1<<7))
#define tstSpeedDown			(pinj_pos & (1<<6))
#define tstJump					(pinj_pos & (1<<2))
#define lastLEDStateRight		(ledRow & (1<<0))
#define lastLEDStateLeft		(ledRow & (1<<7))
#define ledNext_on				(PORTA = ledRow & ~(PINC))

#define MAX_DELAY			200				// 200 * 10ms = 2s period time = 0.5Hz
#define MIN_DELAY			3				// 5 * 10ms = 0.05s period time = 20Hz
#define SPEED_CHANGE		20				// 20 * 10ms = 0.2s
#define SPEED_CHANGE_SMALL	5				// 5 * 10ms = 0.05s

/* GLOBAL */
void flankenerkennung(void);
unsigned char pinj_pos, pinj_neg;

int main(void)
{	
	/* INITIALISIERUNG */
	DDRA = 0xFF;			// 1= Output, 0= Input
	DDRJ = 0x00;			// 1= Output, 0= Input
	DDRC = 0x00;			// 1= Output, 0= Input
	
	unsigned char ledRow = 0x00;
	unsigned char programStart = 1;			// 1= program just started
	unsigned char runState = 1;				// 1= run, 0= stop
	unsigned char direction = 1;			// 1= right to left, 0= left to right
	unsigned char isJumping = 0;			// 0= no jumping
	
	unsigned char tBlink_pv = 0;
	unsigned char tBlink_cyc = 100;			// 100 = 1Hz; default value
    
	/* Main Loop */
	while (1){
		if (tstStartStopp){
			if (programStart){
				programStart = 0;
				ledRow |= (1<<0); 
			}
			else if (runState){
				runState = 0;
			}
			else if (!runState){
				runState = 1;
			}
			
		}
		
		else if (tstChangeDir){
			if (direction){
				direction = 0;
			}
			else {
				direction = 1;
			}
		}
		
		if (tstSpeedUp){
			if (tBlink_cyc > 25){
				if (!((tBlink_cyc - SPEED_CHANGE) < MIN_DELAY)){
					tBlink_cyc -= SPEED_CHANGE;
				}
				else {
					tBlink_cyc = MIN_DELAY;
				}
			}
			else{
				if (!((tBlink_cyc - SPEED_CHANGE_SMALL) < MIN_DELAY)){
					tBlink_cyc -= SPEED_CHANGE_SMALL;
				}
				else {
					tBlink_cyc = MIN_DELAY;
				}
			}
			
		}
		
		if (tstSpeedDown){
			
			if (tBlink_cyc > 25){
				if (!((tBlink_cyc + SPEED_CHANGE) > MAX_DELAY)){
					tBlink_cyc += SPEED_CHANGE;
				}
				else {
					tBlink_cyc = MAX_DELAY;
				}
			}
			else{
				tBlink_cyc += SPEED_CHANGE_SMALL;
			}
		}
		
		if (tstJump){
			if (isJumping){
				isJumping = 0;
			}
			else{
				isJumping = 1;
			}
		}
		
		if (!programStart && runState){
			if (tBlink_pv >= tBlink_cyc){
				if (!isJumping){
					if (direction){
						if (!lastLEDStateLeft){
							ledRow = ledRow << 1;
							tBlink_pv = 0;
						}
						else{
							ledRow = 0x00;
							ledRow |= (1<<0);
							tBlink_pv = 0;
						}
					}
					else {
						if (!lastLEDStateRight){
							ledRow = ledRow >> 1;
							tBlink_pv = 0;
						}
						else{
							ledRow = 0x00;
							ledRow |= (1<<7);
							tBlink_pv = 0;
						}
					}
				}
				else{
					if (direction){
						if (!lastLEDStateLeft){
							ledRow <<= 1;
							tBlink_pv = 0;
						}
						else{
							direction = 0;
						}
					}
					else{
						if (!lastLEDStateRight){
							ledRow >>= 1;
							tBlink_pv = 0;
						}
						else{
							direction = 1;
						}
					}
				}

			}
			else{
				tBlink_pv++;
			}
		
			ledNext_on;
		}
		_delay_ms(10);
		flankenerkennung();
    }
}


/* Flankenerkennung PORTJ */
void flankenerkennung(void){
	unsigned char state = PINJ;
	static unsigned char state_old;
	
	pinj_pos = state & ~state_old;
	pinj_neg = ~state & state_old;
	state_old = state;
}