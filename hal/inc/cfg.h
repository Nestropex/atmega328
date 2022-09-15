#ifndef CFG_H
#define CFG_H

/*

NANO V3 Clone
D13 -- PB5(SCK)   D12 -- PB4 (MOSI)
3V3               D11 -- PB3 (MISO)
REF -- AREF       D10 -- PB2 OC1B
A0  -- PC0        D09 -- PB1 OC1A
A1  -- PC1        D08 -- PB0
A2  -- PC2        D07 -- PD7
A3  -- PC3        D06 -- PD6 OC0A
A4  -- PC4        D05 -- PD5 0C0B
A5  -- PC5        D04 -- PD4
A6  -- ADC6       D03 -- PD3
A7  -- ADC7       D02 -- PD2
5V                GND
Rst               Rst -- PC6 (Reset)
GND               RxD -- PD0 (RxD)
VIN               TxD -- PD1 (TxD)

*/

/*
Atmega328p PU (Dip)

NRESET PC6 |1   28| PC5 ADC5/SCL
RXD    PD0 |2   27| PC4 ADC4/SDA
TXD    PD1 |3   26| PC3 ADC3
INT0   PD2 |4   25| PC2 ADC2
INT1   PD3 |5   24| PC1 ADC1
XCK/T0 PD4 |6   23| PC0 ADC0
       VCC |7   22| GND
       GND |8   21| AREF
OSC1   PB6 |9   20| AVCC
OSC2   PB7 |10  19| PB5 SCK
T1     PD5 |11  18| PB4 MISO
AIN0   PD6 |12  17| PB3 MOSI/OC2
AIN1   PD7 |13  16| PB2 SS/OC1B
ICP1   PB0 |14  15| PB1 OC1A

*/


#include "datatypes.h"

#define SYSTEM_CLK 16000000ul
#define TIMER_TIMER0_PRESCALER   256u
#define TIMER_TIMER1_PRESCALER   256u
#define TIMER_TIMER2_PRESCALER   1024u
#define LOOP_MAIN_TIME_MILLIS    1u
#define LOOP_1_TIME_MILLIS       60u
#define LOOP_2_TIME_MILLIS       500u

/*Common baudrates 9600, 57600, 115200, 500000, 1000000*/
#define UART_BAUDRATE           500000u
#define OUT_ONTIME_MICROS       50u // Output pulse is this long


typedef struct input_pin {
    pin_t switch1;
    pin_t switch2;
    pin_t button1;
    pin_t button2;
    pin_t button3;

}cfg_input_pin_t;

typedef struct cfg_output_pin {
    pin_t dir1;
    pin_t dir2;
    pin_t step1;
    pin_t step2;

}cfg_output_pin_t;


static const uint8_t cfg_port_b = 0x38u;
static const uint8_t cfg_port_c = 0x08u;
static const uint8_t cfg_port_d = 0x3cu;             

static const cfg_input_pin_t cfg_pin_input = {
    .switch1 = {.port = 1u, .bit = 1u},
    .switch2 = {.port = 2u, .bit = 4u},
    .button1 = {.port = 1u, .bit = 0u},
    .button2 = {.port = 2u, .bit = 5u},
    .button3 = {.port = 1u, .bit = 2u}
};

static const cfg_output_pin_t cfg_pin_output = {
    .dir1  = {.port = 3u, .bit = 2u},
    .dir2  = {.port = 3u, .bit = 4u},
    .step1 = {.port = 3u, .bit = 3u},
    .step2 = {.port = 3u, .bit = 5u}
};        

// Pin shall be connected to an LED in order to give an visible alarm
static const pin_t cfg_error_pin = {.port = 1u, .bit = 5u};


#endif