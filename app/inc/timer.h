#ifndef TIMER_H
#define TIMER_H

#include "datatypes.h"
#include "isr.h"

typedef enum timer {
    Timer0 = 0u,
    Timer1,
    Timer2   
}timer_t;

/**
 * @brief Resets config regs and starts the timer 
 *        by configuring the prescaler. 
 * @param clk main system clk
 * @param prescaler divides the clk and sources the timer
 */
uint32_t timer0_init(uint32_t clk, uint16_t prescaler);

/**
 * @brief Init for timer 1
 */
uint32_t timer1_init(uint32_t clk, uint16_t prescaler);
/**
 * @brief Init for timer 2
 */
uint32_t timer2_init(uint32_t clk, uint16_t prescaler);

/**
 * @brief Returns current count of timer 0.
 *        Timer 0 is an 8 bit timer
 * 
 * @return 8 bit current timer count 
 */
uint8_t timer0_get_ticks(void);

/**
 * @brief Returns current count of timer 1.
 *        Timer 1 is a 16 bit timer
 * 
 * @return 16 bit current timer count 
 */
uint16_t timer1_get_ticks(void);

/**
 * @brief Returns current count of timer 2.
 *        Timer 2 is 8 bit timer
 * 
 * @return 8 bit current timer count 
 */
uint8_t timer2_get_ticks(void);

/**
 * @brief Sets a compare value for all three timer 0,1 and 2
 * 
 * @param port port b,c and d correspond to 1,2 and 3
 * @param pin 0 to 7, corresponds to pin number i.e pb5: port 1, pin 5
 * @param comp_val value that is used to trigger ISR on compare match
 *                 timer 0 and 2 are 8 bit timers, value must not exceed 255
 */
void timer_set_compare(interrupts_t nmb, uint16_t comp_val);

#endif