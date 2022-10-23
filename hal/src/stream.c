// Short description 
//
//


//-------Includes-------

#include "datatypes.h"
#include "fifo.h"
#include "stream.h"


//-------Defines-------



//-------TYPES-------



//-------Variables-------
#define MAX_MSG_OBJECTS 120u


static msg_t message[MAX_MSG_OBJECTS];
list_t stream = {message, message};


//-------Static Function Declaration-------



//-------Function Definition-------

void stream_write(list_t *list)
{
    uint8_t data;
    while (list->head != list->tail)
    {
        data = fifo_read(list);
        fifo_write(&stream, &data, 1u);
    }

    uart_fast_byte_transmit(&stream.tail->data);
    stream.tail++;
}

void stream_read(list_t *list)
{

}