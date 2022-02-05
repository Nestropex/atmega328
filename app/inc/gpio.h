#ifndef GPIO_H
#define GPIO_H

#include "datatypes.h"


/**
 * @brief Sets pins as input or output
 * 
 * @param port 0-3
 * @param pin_config bitwise 1 output 0 input 
 * @param dir 0 input, 1 output
 * @return 0 in case of error 
 */
uint8_t GPIO_setup(uint8_t port, uint8_t pin_config);


#endif