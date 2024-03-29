#ifndef OS_H
#define OS_H

#include "datatypes.h"



typedef struct period {
    uint32_t time;
    uint32_t cnt;
    uint16_t time_config;
    uint8_t execute_flag;
    uint32_t cur_ticks;
    uint32_t last_ticks;
    uint32_t diff;
}period_t;



/**
 * @brief This module requires timer1 to be initialized
 * 
 */

/**
 * @brief Fills requested loop object with time since the last execution 
 *        of this function and number of executions since stat up
 *        It will set the execution_flag to 1 if the time since it was set the last
 *        time is elapsed which is configured in execution time.
 * 
 *        This function must be called each main loop, the execution_flag is then,
 *        intended as if() to achieve the desired timing. 
 * 
 * @param loop Object to fill with requested info
 */
void period_control(period_t  *loop);

/**
 * @brief Sends looptime, loopcount etc. of requested object via uart
 * 
 *        Debug purpose only
 * 
 * @param loop Info of this object will be send 
 * @param str Text that shall be visible on serial monitor
 */
void period_print(period_t *loop, uint8_t *str);

/**
 * @brief Sets Timer0 overflow interrupt 
 * 
 */
void period_init(void);




#endif