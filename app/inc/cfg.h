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
const uint8_t gc_portb_cfg = 0xffU;
const uint8_t gc_portc_cfg = 0x03U;
const uint8_t gc_portd_cfg = 0x00U;



#endif