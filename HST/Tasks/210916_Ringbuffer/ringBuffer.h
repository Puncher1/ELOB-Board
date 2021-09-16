/*
 * ringBuffer.h
 *
 * Created: 16.09.2021 08:22:22
 *  Author: Andrin
 */ 


#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

// *** DEFINES ***
#define BUFFER_SIZE			10
#define STATE_OK			0
#define STATE_ERROR			-1

int8_t setRingBuffer(uint8_t data);
int8_t getRingBuffer(uint8_t *pData);
uint8_t sizeRingBuffer(void);

#endif /* RINGBUFFER_H_ */