#ifndef UART_H
#define UART_H

#include "datatypes.h"



/**
 * @brief Sets baudrate to 9600,
 *        also parameters like stop bits, 
 *        parity bit and bit size
 */
void uart_init(void);

/**
 * @brief Transmits null terminated data 
 *        which can be viewed on a serial monitor
 * 
 * @param str pointer to data that has null termination
 * @return    Number of transmitted bytes (Including null termination)
 */
uint8_t uart_str_transmit(uint8_t *str);

/**
 * @brief Converts a number to a string and transmits
 *        in order to view on a serial monitor
 * @param n 4 byte number that shall be transmitted
 * @param base 10 for decimal, 16 for hex etc.
 */
void uart_nmb_transmit(unsigned long n, uint8_t base);

#endif