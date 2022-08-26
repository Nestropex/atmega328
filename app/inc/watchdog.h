#ifndef watchdog_H
#define watchdog_H

/**
 * @brief Reset the watchdog timer to avoid a shut down
 */
void watchdog_reset(void);

/**
 * @brief Sets wdt change enable and wdt disable consecutively
 */
void watchdog_disable(void);


/**
 * @brief Enables the Watchdog Timer in Reset mode after a the timeout is elapsed
 * 
 * @param timeout  in seconds, 1s, 2s and 4s available
 */
uint8_t watchdog_init(uint8_t timeout);

#endif