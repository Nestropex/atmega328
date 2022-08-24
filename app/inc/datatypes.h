#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdint.h>

#define PIN_IN  0u
#define PIN_OUT 1u
typedef enum
{
    no_error = 0u,
    error = 1u
}error_t;

typedef struct pin {
    uint8_t port;
    uint8_t bit;
    uint8_t state;

}pin_t;


#endif