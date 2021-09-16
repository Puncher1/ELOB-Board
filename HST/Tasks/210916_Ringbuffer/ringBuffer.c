/*
 * ringBuffer.c
 *
 * Created: 16.09.2021 08:22:31
 *  Author: Andrin
 */ 


// *** INCLUDES ***
#include <avr/io.h>
#include "ringBuffer.h"


// *** GLOBAL ***
unsigned char isBufferEmpty = 0;
unsigned char isBufferFull = 0;

int8_t bufferArray[BUFFER_SIZE];
unsigned char writeIndex = 0;
unsigned char readIndex = 0;


// *** FUNCTIONS ***

/*
 * @brief Writes into ring buffer
 * @params:
 *		data: The data which should written into the ring buffer
 * @return: State case (Error, Okay)
 */
int8_t setRingBuffer(uint8_t data){
	isBufferEmpty = 0;
	
	if (isBufferFull){
		return STATE_ERROR;
	}
	else{
		bufferArray[writeIndex] = data;
		writeIndex++;
		
		if (readIndex == BUFFER_SIZE){
			readIndex = 0;
		}
		if (readIndex == writeIndex){
			isBufferEmpty = 1;
		}
		return STATE_OK;
	}
}

/*
 * @brief Reads from ring buffer
 * @params:
 *		data: The pointer of the data which should read from the ring buffer
 * @return: State case (Error, Okay)
 */
int8_t getRingBuffer(uint8_t *pData){
	isBufferFull = 0;
	
	if (isBufferEmpty){
		return STATE_ERROR;
	}
	else{
		*pData = bufferArray[readIndex];
		readIndex++;
		
		if (readIndex == BUFFER_SIZE){
			readIndex = 0;
		}
		if (readIndex == writeIndex){
			isBufferEmpty = 1;
		}
		return STATE_OK;
	}
}

/*
 * @brief Gets size of ring buffer
 * @return: Size of ring buffer
 */
uint8_t sizeRingBuffer(void){
	if (isBufferEmpty){
		return STATE_OK;
	}
	else if (isBufferFull){
		return BUFFER_SIZE;
	}
	else if (readIndex > writeIndex){
		return BUFFER_SIZE - (readIndex - writeIndex);
	}
	else{
		return writeIndex - readIndex;
	}
}