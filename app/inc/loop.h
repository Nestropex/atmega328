#ifndef OS_H
#define OS_H

#include "datatypes.h"



typedef struct loop {
    uint32_t time;
    uint32_t cnt;
    uint32_t cur_ticks;
    uint32_t last_ticks;
    uint32_t diff;
}loop_t;

void loop_update(loop_t  *period);

void loop_print(loop_t *period, uint8_t *str);




#endif