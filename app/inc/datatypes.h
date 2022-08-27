#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdint.h>

#define PIN_IN  0u
#define PIN_OUT 1u
#define NULL_PTR (void *)0
#define REG_RESET 0u
typedef enum
{
    no_error = 0u,
    error = 1u
}error_t;

typedef struct pin {
    uint8_t port;
    uint8_t bit;
}pin_t;

typedef struct input {
    pin_t switch1;
    pin_t switch2;
    pin_t button1;
    pin_t button2;
    pin_t button3;

}input_t;

typedef struct output {
    pin_t dir1;
    pin_t dir2;
    pin_t step1;
    pin_t step2;

}output_t;



#endif