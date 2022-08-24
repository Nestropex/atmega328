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

#endif