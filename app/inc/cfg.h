#ifndef CFG_H
#define CFG_H

/*

NANO V3 Clone
D13 -- PB5(SCK)   D12 -- PB4 (MOSI)
3V3               D11 -- PB3 (MISO)
REF -- AREF       D10 -- PB2
A0  -- PC0        D09 -- PB1
A1  -- PC1        D08 -- PB0
A2  -- PC2        D07 -- PD7
A3  -- PC3        D06 -- PD6
A4  -- PC4        D05 -- PD5
A5  -- PC5        D04 -- PD4
A6  -- ADC6       D03 -- PD3
A7  -- ADC7       D02 -- PD2
5V                GND
Rst               Rst -- PC6 (Reset)
GND               RxD -- PD0 (RxD)
VIN               TxD -- PD1 (TxD)

*/



#include "datatypes.h"

#define SYSTEM_CLK 16000000u
#define TIMER_16BIT_PRESCALER   256u

static const uint8_t gc_portb_dir[] = {
                                PIN_IN,  // Pin 0
                                PIN_IN,  // Pin 1
                                PIN_IN,  // Pin 2
                                PIN_IN,  // Pin 3
                                PIN_IN,  // Pin 4
                                PIN_OUT, // Pin 5
                                PIN_IN,  // Pin 6
                                PIN_IN   // Pin 7
                                };

static const uint8_t gc_portc_dir[] = {
                                PIN_IN,  // Pin 0
                                PIN_IN,  // Pin 1
                                PIN_IN,  // Pin 2
                                PIN_IN,  // Pin 3
                                PIN_IN,  // Pin 4
                                PIN_IN,  // Pin 5
                                PIN_IN,  // Pin 6 Reset must must remain INPUT!!!
                                PIN_IN   // Pin 7
                                };
static const uint8_t gc_portd_dir[] = {
                                PIN_IN,  // Pin 0
                                PIN_IN,  // Pin 1
                                PIN_OUT, // Pin 2
                                PIN_OUT, // Pin 3
                                PIN_OUT, // Pin 4
                                PIN_OUT, // Pin 5
                                PIN_IN,  // Pin 6
                                PIN_IN   // Pin 7
                                };               

static const input_t g_in = {
    .switch1 = {.port = 1u, .bit = 1u},
    .switch2 = {.port = 2u, .bit = 4u},
    .button1 = {.port = 1u, .bit = 0u},
    .button2 = {.port = 2u, .bit = 5u},
    .button3 = {.port = 1u, .bit = 2u}
};

static const output_t g_out = {
    .dir1  = {.port = 3u, .bit = 2u},
    .dir2  = {.port = 3u, .bit = 4u},
    .step1 = {.port = 3u, .bit = 3u},
    .step2 = {.port = 3u, .bit = 5u}
};        

// Pin shall be connected to an LED in order to give an visible alarm
static const pin_t g_error_out = {.port = 1u, .bit = 5u};




/*

   pin_t dir1  = {.port = 3u, .bit = 2u,.state = 0u};
    pin_t step1 = {.port = 3u, .bit = 3u,.state = 0u};
    pin_t dir2  = {.port = 3u, .bit = 4u,.state = 0u};
    pin_t step2 = {.port = 3u, .bit = 5u,.state = 0u};

    pin_t switch1  = {.port = 1u, .bit = 1u,.state = 0u};
    pin_t switch2  = {.port = 2u, .bit = 4u,.state = 0u}; 
    pin_t button1  = {.port = 1u, .bit = 0u,.state = 0u}; 
    pin_t button2  = {.port = 2u, .bit = 5u,.state = 0u}; 
    pin_t button3  = {.port = 1u, .bit = 2u,.state = 0u};*/
#endif