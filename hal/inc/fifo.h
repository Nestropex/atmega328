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

void fifo_init(list_t *list, msg_t *message);

void fifo_write(list_t *list, uint8_t *data, uint8_t cnt);

void fifo_send(list_t *list);

#endif