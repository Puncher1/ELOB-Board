/*
 * ELOB Board ATmega2560.c
 *
 * Created: 19.08.2021 12:55:49
 * Author : Puncher1
 *
 * Description: Turns on the next LED when pressing the button (starts at 0).
 *
 */ 

#include <avr/io.h>

#define F_CPU 8000000		// CPU operating frequency: 8MHz
#include <util/delay.h>

#define buttonState			(PINJ & (1<<7))

int main(void)
{
    /* INITIALIZATION */
	
	// LED Port
	DDRA = 0xFF;			// 1= Output, 0= Input
	// Button Port
	DDRJ = 0x00;			// 1= Output, 0= Input
	
	int ledCount = 7;
	int currentButtonState = 0;

	PORTA = 0x00;			// sets LEDs to 0 by default
    
	while (1) 
    {
		if (buttonState){
			if (!currentButtonState){					
				currentButtonState = 1;
				if (ledCount >= 0){
					PORTA |=(1<<ledCount);			// sets next LED to 1 
					ledCount--;
				}
				else {
					PORTA = 0x00;					// sets all LEDs to 0 after last LED
					ledCount = 7;
				}
			}
			_delay_ms(200);							// for debouncing; bad way to wait though (just for test porpuses)
			
		}
		else {
			currentButtonState = 0;
		}
		
    }
}

