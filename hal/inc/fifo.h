#ifndef FIFO_H
#define FIFO_H

// Short description 
//
//


//-------Includes-------
#include "datatypes.h"



//-------Defines-------




//-------TYPES-------

typedef struct msg{
    struct msg *next;
    uint8_t data;

}msg_t;

typedef struct list{
    msg_t *head;
    msg_t *tail;
}list_t;


//-------Variables-------



//-------Function Declaration-------

/**
 * @brief Initializes list with message
 * 
 * @param list pointer to fifo
 * @param message base pointer of data
 */
void fifo_init(list_t *list, msg_t *message);

/**
 * @brief Writes data into fifo 
 * 
 * @param list pointer to fifo
 * @param data base pointer of data to write
 * @param cnt  number of bytes to write
 */
void fifo_write(list_t *list, uint8_t *data, uint8_t cnt);

/**
 * @brief writes to stream and sends the first byte
 * 
 * @param list pointer to fifo
 */
void fifo_send(list_t *list);

/**
 * @brief Reads data from fifo, one byte per call
 *        Must be only called aslong head is unequal tail!
 * @param list pointer to fifo
 * @return data bytewise
 */
uint8_t  fifo_read(list_t *list);

#endif