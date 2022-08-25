#ifndef UART_H
#define UART_H

#include "datatypes.h"




uint8_t uart_set_baudrate(uint32_t baudrate);
uint8_t uart_transmit(uint8_t *data, uint8_t count);

#endif