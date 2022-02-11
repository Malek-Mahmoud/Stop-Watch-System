/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASiel
 */

#include "stopwatch.h"
#include<avr/interrupt.h>
#include<avr/delay.h>
extern char sec,min,hour;
int main()
{
	DDRC  |= 0X0F; //DECODER O/P PINS
	PORTC &= 0XF0;
	DDRA  |= 0X3F; //NPNs O/P PINS
	PORTA &= 0XC0;
	SREG  |= (1<<7); //SET GLOBAL INTERRUPT BIT
	/******** FUNCTION CALLS *************/
	init_INIT0();
	init_INIT1();
	init_INIT2();
	init_timer1_compare_mode();
	/************************************/
	while(1)
	{
		/********************** MAIN ROUTINE ********************/
		/************* SELECT ONE OF THE 7 SEGMENTS *************/
		/*************** THEN DISPLAY ITS NUMBER ****************/
		/******* REPEAT THIS SEQUANCE WITH ALL SEGMENTS *********/
		/***** a slight delay between every sequence ************/
		PORTA = (PORTA&0XC0)|((1<<0)&0X3F);
		PORTC = (PORTC & 0XF0)|(sec % 10);
		_delay_ms(5);
		PORTA = (PORTA&0XC0)|((1<<1)&0X3F);
		PORTC = (PORTC & 0XF0)|(sec / 10);
		_delay_ms(5);
		PORTA = (PORTA&0XC0)|((1<<2)&0X3F);
		PORTC = (PORTC & 0XF0)|(min % 10);
		_delay_ms(5);
		PORTA =(PORTA&0XC0)|((1<<3)&0X3F);
		PORTC =(PORTC & 0XF0)|(min / 10);
		_delay_ms(5);
		PORTA = (PORTA&0XC0)|((1<<4)&0X3F);
		PORTC = (PORTC & 0XF0)|(hour % 10);
		_delay_ms(5);
		PORTA = (PORTA&0XC0)|((1<<5)&0X3F);
		PORTC =(PORTC & 0XF0)|(hour / 10);
		_delay_ms(5);
		/********************************************************/
	}
	return 0;
}
/************ INTERRUPT HANDLER ************/
ISR(TIMER1_COMPA_vect)
{
	/**** TIME COUNTING ROUTINE *****/
	stopwatch_handler();
	/*******************************/
}
ISR(INT0_vect)
{
	/************** RESET ROUTINE **************/
	/*****  CLEARING THE COUNTING VARIABLES ****/
	sec = 0;
	min = 0;
	hour= 0;
	/******************************************/
}
ISR(INT1_vect)
{
	/****************** PAUSE ROUTINE *********************/
	/***** STOP THE TIMER MODULE BY CLEARING THE CLOCK ****/
	TCCR1B &= ~(1<<CS12);
	TCCR1B &= ~(1<<CS11);
	TCCR1B &= ~(1<<CS10);
	/******************************************************/
}
ISR(INT2_vect)
{
	/**** RESUME ROUTINE *****/
	TCCR1B |= (1<<CS11) | (1<<CS10); //RESTORE THE TIMER BY SETTING THE CLOCK "F_CPU/64"
	/*************************/
}
/*******************************************/
