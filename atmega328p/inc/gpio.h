#ifndef GPIO_H
#define GPIO_H

#include "datatypes.h"


/**
 * @brief Sets pins as input or output
 * 
 * @param port port b,c and d correspond to 1,2 and 3
 * @param pin_config bitwise 1 output 0 input 
 */
void gpio_init(uint8_t port, const uint8_t pin_config);

/**
 * @brief Sets pins as high or low
 * 
 * @param port port b,c and d correspond to 1,2 and 3
 * @param pin 0 to 7, corresponds to pin number i.e pb5: port 1, pin 5
 * @param state 0 low 1 high
 */
void gpio_write(uint8_t port, uint8_t pin, uint8_t state);

/**
 * @brief Gives the current state of a requested pin 
 * 
 * @param port port b,c and d correspond to 1,2 and 3
 * @param pin 0 to 7, corresponds to pin number i.e pb5: pin 5
 * @return current state of the pin 0 for low 1 for high 
 *         0xff means error
 */
uint8_t gpio_read(uint8_t port, uint8_t pin);

/**
 * @brief Pulses output pin with requested frequency
 * @param port port b,c and d correspond to 1,2 and 3
 * @param pin  corresponds to pin number i.e pb5: port 1, pin 5
 * 
 */
void gpio_flash(uint8_t port, uint8_t pin);

/**
 * @brief Reads requested output pin and writes the opposite
 * 
 */
void gpio_toggle(uint8_t port, uint8_t pin);

#endif