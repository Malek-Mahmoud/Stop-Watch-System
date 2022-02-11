/*
 * stopwatch.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASiel
 */

#include "stopwatch.h"
/************* GLOBAL VARIABLES *************/
char sec=0,min=0,hour=0;
/********************************************/
/************* FUNCTION DEFINATIONS **********/
void init_timer1_compare_mode(void)
{
	TCNT1 = 0;
	OCR1A = 15625;
	TIMSK |=(1<<OCIE1A);
	TCCR1A = (1<<FOC1A);
	TCCR1B = (1<<CS11) | (1<<CS10) | (1<<WGM12);
}
void stopwatch_handler(void)
{
	/******** SEC HANDLER **********/
	sec++;
	if(60 == sec)
	{
		sec = 0;
		min++;
	}
	/******** MIN HANDLER **********/
	if(60 == min)
	{
		min = 0;
		hour++;
	}
	/******** HOUR HANDLER *********/
	if(24 == hour)
	{
		hour = 0;
		sec  = 0;
		min  = 0;
	}
}
void init_INIT0(void)
{
	DDRD  &= ~(1<<PD2);
	PORTD |=  (1<<PD2);
	MCUCR |=  (1<<ISC01); //FALLING EDGE
	MCUCR &= ~(1<<ISC00); //FALLING EDGE
	GICR  |=  (1<<INT0);
}
void init_INIT1(void)
{
	DDRD  &= ~(1<<PD3);
	MCUCR |=  (1<<ISC11)|(1<<ISC10); //RISING EDGE
	GICR  |=  (1<<INT1);
}
void init_INIT2(void)
{
	DDRB  &= ~(1<<PB2);
	PORTB |=  (1<<PB2);
	MCUCR &= ~(1<<ISC2); //FALLING EDGE
	GICR  |=  (1<<INT2);
}
/********************************************/
