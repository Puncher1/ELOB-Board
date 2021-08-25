/*
 * Testing.c
 *
 * Created: 19.08.2021 15:49
 * Author : Puncher1
 *
 * Description: Some tests with the ELOB Board
 *
 */ 

#include <avr/io.h>

#define F_CPU 8000000		// 8MHz
#include <util/delay.h>

#define buttonON		(PINJ &= (1<<0))
#define buttonOFF		(PINJ &= (1<<7))

void buzzer1kHz(){
	PORTD |= (1<<7);
	_delay_ms(10);
	PORTD &= ~(1<<7);
	_delay_ms(10);
}

void buzzerStop(){
	PORTD &= ~(1<<7);
}

int main(void)
{
    /* INITIALIZATION */
	DDRD = 0xFF;				// 1= Output, 0= Input
	
    /* Program Loop */
	
	int buzzerState = 0;
	while (1) 
    {
		if (buttonON){
			buzzerState = 1;
		}
		else if (buttonOFF){
			buzzerState = 0;
		}
		
		if (buzzerState){
			
			for (int index = 0; index < 50; index++){
				buzzer1kHz();
				_delay_ms(10);
			}
			
			for (int index = 0; index < 50; index++){
				buzzerStop();
				_delay_ms(10);
			}
		}
		
		
	}
}

