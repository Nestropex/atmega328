#ifndef STREAM_H
#define STREAM_H

// Short description 
//
//


//-------Includes-------

#include "datatypes.h"
#include "fifo.h"


//-------Defines-------




//-------TYPES-------



//-------Variables-------



//-------Function Declaration-------
/**
 * @brief Writes to the fifo that interacts with the peripheral
 * 
 * @param list pointer to fifo
 */
void stream_write(list_t *list);

/**
 * @brief Reads from the fifo that interacts with the peripheral
 * 
 * @param list pointer to fifo
 */
void stream_read(list_t *list);


#endif