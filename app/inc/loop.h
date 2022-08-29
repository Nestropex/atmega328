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

/**
 * @brief Fills requested loop object with time since the last execution 
 *        of this function and number of executions since stat up
 * 
 *        Shall be called everywhere where periodic timining must be monitored 
 * 
 * @param period Object to fill with requested info
 */
void loop_update(loop_t  *period);

/**
 * @brief Sends looptime and loopcount of requested object via uart
 * 
 *        Debug purpose only
 * 
 * @param period Info of this object will be send 
 * @param str Text that shall be visible on serial monitor
 */
void loop_print(loop_t *period, uint8_t *str);




#endif