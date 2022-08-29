#ifndef OS_H
#define OS_H

#include "datatypes.h"



typedef struct loop {
    uint16_t time;
    uint32_t cnt;
    uint16_t time_config;
    uint8_t execute_flag;
    uint16_t cur_ticks;
    uint16_t last_ticks;
    uint16_t diff;
}loop_t;

/**
 * @brief Fills requested loop object with time since the last execution 
 *        of this function and number of executions since stat up
 * 
 *        Shall be called everywhere where periodic timining must be monitored 
 * 
 * @param period Object to fill with requested info
 */
void loop_control(loop_t  *period);

/**
 * @brief Sends looptime and loopcount of requested object via uart
 * 
 *        Debug purpose only
 * 
 * @param period Info of this object will be send 
 * @param str Text that shall be visible on serial monitor
 */
void loop_print(loop_t *period, uint8_t *str);

/**
 * @brief 
 * 
 */
void loop_time_elapsed(loop_t *period);




#endif