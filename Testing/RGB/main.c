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

void blue(){
	PORTB |= (1<<7);
	_delay_ms(0.1);
	PORTB &= ~(1<<7);
	_delay_ms(10);
}

void cyan(){
	PORTB |= (1<<7);
	PORTB |= (1<<6);
	_delay_ms(0.1);
	PORTB &= ~(1<<7);
	PORTB &= ~(1<<6);
	_delay_ms(10);
}

void green(){
	PORTB |= (1<<6);
	_delay_ms(0.1);
	PORTB &= ~(1<<6);
	_delay_ms(10);
}

void yellow(){
	PORTB |= (1<<5);
	PORTB |= (1<<6);
	_delay_ms(0.1);
	PORTB &= ~(1<<5);
	PORTB &= ~(1<<6);
	_delay_ms(10);
}

void red(){
	PORTB |= (1<<5);
	_delay_ms(0.1);
	PORTB &= ~(1<<5);
	_delay_ms(10);
}

void magenta(){
	PORTB |= (1<<5);
	PORTB |= (1<<7);
	_delay_ms(0.1);
	PORTB &= ~(1<<5);
	PORTB &= ~(1<<7);
	_delay_ms(10);
}

int main(void)
{
    /* INITIALIZATION */
	DDRB = 0xFF;				// 1= Output, 0= Input
	
	
	int currentColor = 0;
    /* Program Loop */
	while (1) 
    {
		if (currentColor == 0){
			for (int index = 0; index <= 50; index++) {
				blue();
				_delay_ms(5);								// Keep color 250ms
			}
			currentColor = 1;
				
		}
		else if (currentColor == 1){
			for (int index = 0; index <= 50; index++) {
				cyan();
				_delay_ms(5);								// Keep color 250ms
			}
			currentColor = 2;
		}
		else if (currentColor == 2){
			for (int index = 0; index <= 50; index++) {
				green();
				_delay_ms(5);								// Keep color 250ms
			}
			currentColor = 3;
		}
		else if (currentColor == 3){
			for (int index = 0; index <= 50; index++) {
				yellow();
				_delay_ms(5);								// Keep color 250ms
			}
			currentColor = 4;
		}
		else if (currentColor == 4){
			for (int index = 0; index <= 50; index++) {
				red();
				_delay_ms(5);								// Keep color 250ms
			}
			currentColor = 5;
		}
		else if (currentColor == 5){
			for (int index = 0; index <= 50; index++) {
				magenta();
				_delay_ms(5);								// Keep color 250ms
			}
			currentColor = 0;
		}
	}
}

