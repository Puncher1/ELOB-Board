/*
 * Reaction tester with a 7-segment-display
 *
 * Author: Puncher1
 * ********************************
 * Date			Vers.	Name				Comment / Change
 * 04.09.2021	1.0		Puncher1			Creation
 */


// *** INCLUDES ***
#include <avr/io.h>

#define F_CPU 8000000		// 8MHz
#include <util/delay.h>

// *** DEFINES ***

// ** Outputs **
#define segmentA_on				(PORTH |= (1<<0))
#define segmentB_on				(PORTH |= (1<<1))
#define segmentC_on				(PORTH |= (1<<2))
#define segmentD_on				(PORTH |= (1<<3))
#define segmentE_on				(PORTH |= (1<<4))
#define segmentF_on				(PORTH |= (1<<5))
#define segmentG_on				(PORTH |= (1<<6))
#define segmentDP_on			(PORTH |= (1<<7))
#define segmentApastrophe_on	(PORTG |= (1<<3))
#define segmentColon_on			(PORTG |= (1<<4))

#define segmentA_off			(PORTH &= ~(1<<0))
#define segmentB_off			(PORTH &= ~(1<<1))
#define segmentC_off			(PORTH &= ~(1<<2))
#define segmentD_off			(PORTH &= ~(1<<3))
#define segmentE_off			(PORTH &= ~(1<<4))
#define segmentF_off			(PORTH &= ~(1<<5))
#define segmentG_off			(PORTH &= ~(1<<6))
#define segmentDP_off			(PORTH &= ~(1<<7))
#define segmentApastrophe_off	(PORTG &= ~(1<<3))
#define segmentColon_off		(PORTG &= ~(1<<4))

#define digitOne_on				((PORTG &= ~(1<<0)) & (PORTG &= ~(1<<1)))
#define digitTwo_on				((PORTG |= (1<<0)) & (PORTG &= ~(1<<1)))
#define digitThree_on			((PORTG &= ~(1<<0)) & (PORTG |= (1<<1)))
#define digitFour_on			((PORTG |= (1<<0)) & (PORTG |= (1<<1)))

#define multiplexer_on			(PORTG |= (1<<2))

// ** Statements **
#define segmentAStatement		(currentDigit == 0 || currentDigit == 2 || currentDigit == 3 || currentDigit == 5 || currentDigit == 6 || currentDigit == 7 || currentDigit == 8 || currentDigit == 9)
#define segmentBStatement		(currentDigit == 0 || currentDigit == 1 || currentDigit == 2 || currentDigit == 3 || currentDigit == 4 || currentDigit == 7 || currentDigit == 8 || currentDigit == 9)
#define segmentCStatement		(currentDigit == 0 || currentDigit == 1 || currentDigit == 3 || currentDigit == 4 || currentDigit == 5 || currentDigit == 6 || currentDigit == 7 || currentDigit == 8 || currentDigit == 9)
#define segmentDStatement		(currentDigit == 0 || currentDigit == 2 || currentDigit == 3 || currentDigit == 5 || currentDigit == 6 || currentDigit == 8 || currentDigit == 9)
#define segmentEStatement		(currentDigit == 0 || currentDigit == 2 || currentDigit == 6 || currentDigit == 8)
#define segmentFStatement		(currentDigit == 0 || currentDigit == 4 || currentDigit == 5 || currentDigit == 6 || currentDigit == 8 || currentDigit == 9)
#define segmentGStatement		(currentDigit == 2 || currentDigit == 3 || currentDigit == 4 || currentDigit == 5 || currentDigit == 6 || currentDigit == 8 || currentDigit == 9 || currentDigit == '-')

#define speed		150

// * GPIO *
struct gpio{
	unsigned char pos;				// var for positive edge
	unsigned char neg;				// var for negative edge
	unsigned char gpio_old;			// var for previous state
	unsigned char *port;			// var for port
};


// *** GLOBAL ***

// ** Function Prototypes **
void edgeDetection(struct gpio*);
void SegmentDisplay(unsigned int, unsigned char, unsigned char, unsigned char);
unsigned int Multiplexer(unsigned int, unsigned char);
void SegmentControl(unsigned int, unsigned char, unsigned char, unsigned char);


/*
 * MAIN-ROUTINE
 */
int main(void){
	
	// *** INITIALIZATION ***
	
	// ** I/O **
	DDRG = 0xFF;
	DDRH = 0xFF;
	
	// ** Local Variables **
	multiplexer_on;
	
	// *** PROGRAM-LOOP ***
	while (1){
	}
}


// *** FUNCTIONS ***

/*
 * @brief: Detects edge for specific port
 * @param myGPIO: Data structur with positive edge, negative edge, previous state and port
 * @return: Data structur with  positive edge, negative edge and previous state
 */
void edgeDetection(struct gpio* myGPIO){
	
	/* ** Local Variables ** */
	unsigned char gpio_port = *myGPIO->port;

	myGPIO->pos = gpio_port & ~myGPIO->gpio_old;
	myGPIO->neg = ~gpio_port & myGPIO->gpio_old;
	myGPIO->gpio_old = gpio_port;	
}

/*
 * @brief: Displays specific number to 7 segment display
 * @param num: The specific number which gets converted
 * @param isColon: Whenever the colon should be set or not
 * @param isApastrophe: Whenever the apastrophe should be set or not
 */
void SegmentDisplay(unsigned int num, unsigned char isLine, unsigned char isColon, unsigned char isApastrophe){
	
	static unsigned char digitPoint = 0;		// 0= first digit, 3= last digit
	
	unsigned int currentDigit = Multiplexer(num, digitPoint);
	SegmentControl(currentDigit, isLine, isColon, isApastrophe);
	
	digitPoint++;
	
	if (digitPoint > 3){
		digitPoint = 0;
	}
}


/*
 * @brief: Sets multiplexer to current digit position
 * @param num: The specific number which gets converted
 * @param digitPoint: the current digit point
 */
unsigned int Multiplexer(unsigned int num, unsigned char digitPoint){
	
	segmentA_off;
	segmentB_off;
	segmentC_off;
	segmentD_off;
	segmentE_off;
	segmentF_off;
	segmentG_off;
	
	switch (digitPoint){
		
		case 0:
			num %= 10;
		
			digitOne_on;
			break;
		
		case 1:
			num %= 100;
			num /= 10;
		
			digitTwo_on;
			break;
		
		case 2:
			num %= 1000;
			num /= 100;
		
			digitThree_on;
			break;
		
		case 3:
			num /= 1000;
		
			digitFour_on;
			break;
	}
	
	return num;	
}

/*
 * @brief: Sets individual segment on 7 segment display
 * @param currentDigit: the current digit at which the multiplexer is
 * @param isColon: Whenever the colon should be set or not
 * @param isApastrophe: Whenever the apastrophe should be set or not
 */
void SegmentControl(unsigned int currentDigit, unsigned char isLine, unsigned char isColon, unsigned char isApastrophe){
	segmentDP_off;
	
	if (isLine){
		segmentG_on;
	}
	else{
		segmentAStatement ? segmentA_on : segmentA_off;
		segmentBStatement ? segmentB_on : segmentB_off;
		segmentCStatement ? segmentC_on : segmentC_off;
		segmentDStatement ? segmentD_on : segmentD_off;
		segmentEStatement ? segmentE_on : segmentE_off;
		segmentFStatement ? segmentF_on : segmentF_off;
		segmentGStatement ? segmentG_on : segmentG_off;
		
		isColon ? segmentColon_on : segmentColon_off;
		isApastrophe ? segmentApastrophe_on : segmentApastrophe_off;
	}

}