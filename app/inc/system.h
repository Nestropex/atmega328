#ifndef SYSTEM_H
#define SYSTEM_H

#include "datatypes.h"

#define ERROR_HANDLER(x) system_error_handler(x)

/**
 * @brief Brings the system to a defined state in case of error.
 *        The error description from the param will be sent via uart 
 *        and can be read via Serial Monitor. 
 *        Also the configured error pin will be flashed
 * 
 * @param error_description a string that holds information where the error occurred
 *                          i.e. module and function name
 */
void system_error_handler(uint8_t *error_description);

#endif