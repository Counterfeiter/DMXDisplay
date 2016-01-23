/*
 * rs485.h
 
// DMX Display Extension
// Copyright (c) 2011-2015 Sebastian Förster
 */ 


#ifndef RS485_H_
#define RS485_H_


#include <asf.h>

#define SIZEOFINCOME	32 + 4


extern uint8_t msg_1[SIZEOFINCOME];
extern volatile uint8_t msg_1_cnt;
extern uint8_t msg_2[SIZEOFINCOME];
extern volatile uint8_t msg_2_cnt;

extern void rs485_init(void);
extern void rs485_deinit(void);
extern uint8_t rs485_add_data(uint8_t *data, uint8_t size);
extern void rs485_init_dma(void);


#endif /* RS485_H_ */