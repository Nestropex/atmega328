#ifndef SYSTEM_H
#define SYSTEM_H

#include "datatypes.h"

#define ERROR_HANDLER(x) system_error_handler(x)

/**
 * @brief Confiures the error led
 * 
 */
void system_init(pin_t error_led);

/**
 * @brief Brings the system to a defined state in case of error.
 *        The error description from the param will be sent via uart 
 *        and can be read via Serial Monitor. 
 *        Also the configured error pin will be flashed.
 * 
 *        This function should be called in case of NULL pointer or switch break statement or
 *        everywhere where a configuration error can occurre. 
 * 
 * @param error_description a string that holds information about the occurred error
 *                          i.e. function name
 */
void system_error_handler(uint8_t *error_description);

/**
 * @brief Will check at every call whether an error has occurred. 
 *        This will prevent an error to be overseen 
 *        in case it occurred only once at start up. 
 * 
 *        This Function should be called periodically, i.e. every loop
 */
void system_error_update(void);

#endif