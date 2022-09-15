#ifndef INPUT_H
#define INPUT_H

#include "datatypes.h"
#include "period.h"

typedef struct input{
        uint16_t  ONtime;
        uint8_t   state;
        pin_t     pin;
        period_t *loop;
}input_t;


/**
 * @brief Updates input object with input state and the time it has been on
 * 
 * @param object pointer to input object as switch or button
 */
void input_get(input_t *object);


#endif