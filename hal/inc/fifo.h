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
    int8_t *next;
    uint8_t data;

}msg_t;

typedef struct list{
    int8_t last;
    int8_t first;
}list_t;


//-------Variables-------



//-------Function Declaration-------
void fifo_init(void);


#endif