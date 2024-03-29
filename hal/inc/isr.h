#ifndef ISR_H
#define ISR_H

#include "datatypes.h"



typedef enum interrupts {
    Timer0_Comp_A = 0u,
    Timer0_Comp_B ,
    Timer0_OVF    ,
    Timer1_Comp_A ,
    Timer1_Comp_B ,
    Timer1_OVF    ,
    Timer2_Comp_A ,
    Timer2_Comp_B ,
    Timer2_OVF,
    Uart_tx
}interrupts_t;


/**
 * @brief Enables the interrupts globally by calling assembler instruction.
 * 
 */
void isr_init(void);

/**
 * @brief Enables the requested interrupt and allocates an interrupt service routine.
 *              
 *        This function must be executed after the timer initialization
 * 
 * @param nmb Requested interrupt as listed in enum
 */
void isr_register(void (*isr), interrupts_t nmb);

#endif