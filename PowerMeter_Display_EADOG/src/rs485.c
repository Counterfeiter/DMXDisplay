/*
 * rs485.c
 *
// DMX Display Extension
// Copyright (c) 2011-2015 Sebastian Förster
 */ 


#include "rs485.h"

uint8_t msg_1[SIZEOFINCOME];
volatile uint8_t msg_1_cnt = 0;
uint8_t msg_2[SIZEOFINCOME];
volatile uint8_t msg_2_cnt = 0;

ISR(USARTC0_RXC_vect) 
{
	//break ?
	if(USARTC0.STATUS & USART_FERR_bm) {
		msg_1_cnt = 0;
		uint8_t temp = USARTC0.DATA;
	} else {
		
		if(msg_1_cnt < sizeof(msg_1)) {
			msg_1[msg_1_cnt] = USARTC0.DATA;
			msg_1_cnt++;
		} else {
			uint8_t temp = USARTC0.DATA;
		}
	}
		
}

ISR(USARTC1_RXC_vect)
{
	//break ?
	if(USARTC1.STATUS & USART_FERR_bm) {
		msg_2_cnt = 0;
		uint8_t temp = USARTC1.DATA;
	} else {
		
		if(msg_2_cnt < sizeof(msg_2)) {
			msg_2[msg_2_cnt] = USARTC1.DATA;
			msg_2_cnt++;
		} else {
			uint8_t temp = USARTC1.DATA;
		}
	}
}

void rs485_init(void)
{
	
	ioport_configure_pin(IOPORT_CREATE_PIN(PORTC, 3), IOPORT_DIR_OUTPUT	| IOPORT_INIT_HIGH);
	ioport_configure_pin(IOPORT_CREATE_PIN(PORTC, 2), IOPORT_DIR_INPUT);
	
	ioport_configure_pin(IOPORT_CREATE_PIN(PORTC, 7), IOPORT_DIR_OUTPUT	| IOPORT_INIT_HIGH);
	ioport_configure_pin(IOPORT_CREATE_PIN(PORTC, 6), IOPORT_DIR_INPUT);
		
	//rs485 enable
	usart_rs232_options_t usart_opt;
	
	usart_opt.baudrate = 250000;
	usart_opt.charlength = USART_CHSIZE_8BIT_gc;
	usart_opt.paritytype = USART_PMODE_DISABLED_gc;
	usart_opt.stopbits = true;
	
	usart_init_rs232(&RS485_1_UART,&usart_opt);
	
	usart_set_rx_interrupt_level(&RS485_1_UART,USART_INT_LVL_HI);
	
	
	
	usart_init_rs232(&RS485_2_UART,&usart_opt);
	
	usart_set_rx_interrupt_level(&RS485_2_UART,USART_INT_LVL_HI);
}

void rs485_deinit(void)
{
	sysclk_disable_peripheral_clock(&RS485_1_UART);	
	sysclk_disable_peripheral_clock(&RS485_2_UART);
	
	ioport_configure_pin(IOPORT_CREATE_PIN(PORTC, 3), IOPORT_DIR_INPUT);
	ioport_configure_pin(IOPORT_CREATE_PIN(PORTC, 2), IOPORT_DIR_INPUT);
	
	ioport_configure_pin(IOPORT_CREATE_PIN(PORTC, 7), IOPORT_DIR_INPUT);
	ioport_configure_pin(IOPORT_CREATE_PIN(PORTC, 6), IOPORT_DIR_INPUT);
	
	//dma_disable();
}