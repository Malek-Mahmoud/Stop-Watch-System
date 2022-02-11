/*
 * stopwatch.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ASiel
 */

#ifndef STOPWATCH_H_
#define STOPWATCH_H_
/**************** LIBRARIES *****************/
#include<avr/io.h>
/********************************************/
/*********** FUNCTION PROTOTYPES ************/
void init_timer1_compare_mode(void);
void init_INIT0(void);
void init_INIT1(void);
void init_INIT2(void);
void stopwatch_handler(void);
/********************************************/
#endif /* STOPWATCH_H_ */
