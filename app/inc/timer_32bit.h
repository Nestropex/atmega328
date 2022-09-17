#ifndef timer_32bit_H
#define timer_32bit_H

// Short description 
//
//


//-------Includes-------

#include "datatypes.h"



//-------Defines-------




//-------TYPES-------



//-------Variables-------



//-------Function Declaration-------

/**
 * @brief Sets up Interrupts for timer 0
 * 
 */
void timer_32bit_init(void);

/**
 * @brief Function or's 8 bit hw timer with 32 bit value that increases on every overflow
 * 
 * @return a 32 bit timer value based on real 8 bit timer
 */
uint32_t timer0_32_get_ticks(void);

/**
 * @brief Function or's 8 bit hw timer with 32 bit value that increases on every overflow
 * 
 * @return a 32 bit timer value based on real 8 bit timer
 */
uint32_t timer1_32_get_ticks(void);

/**
 * @brief Function or's 8 bit hw timer with 32 bit value that increases on every overflow
 * 
 * @return a 32 bit timer value based on real 8 bit timer
 */
uint32_t timer2_32_get_ticks(void);

#endif