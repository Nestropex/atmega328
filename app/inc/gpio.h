#ifndef GPIO_H
#define GPIO_H

#include "datatypes.h"


/**
 * @brief Sets pins as input or output
 * 
 * @param port 0-3
 * @param pin_config bitwise 1 output 0 input 
 * @param dir 0 input, 1 output
 */
void GPIO_setup(uint8_t port, uint8_t pin_config);

/**
 * @brief Sets pins as high or low
 * 
 * @param port 0-3
 * @param pin 0 to 7
 * @param state 0 low 1 high
 */
void GPIO_write(uint8_t port, uint8_t pin, uint8_t state);

/**
 * @brief Gives the current state of a requested pin 
 * 
 * @param port 0-3
 * @param pin 0 to 7
 * @return current state of the pin 0 for low 1 for high 
 *         0xff means error
 */
uint8_t GPIO_read(uint8_t port, uint8_t pin);

#endif