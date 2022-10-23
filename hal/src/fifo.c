// Short description 
//
//


//-------Includes-------

#include "datatypes.h"
#include "fifo.h"


//-------Defines-------



//-------TYPES-------



//-------Variables-------


//-------Static Function Declaration-------



//-------Function Definition-------

void fifo_init(list_t *list, msg_t *message)
{
    list->tail = message;
    list->head = message;
    uint8_t size;
   // uart_cnt_transmit(size,2u);
}

void fifo_write(list_t *list, uint8_t *data, uint8_t cnt)
{
    
    for (uint8_t i = 0u; i < cnt; i++)
    {
        if (list->tail == list->head)
        {
            list->head->data = *data;
            list->head++; 
        }
        else
        {
            list->head->data = *(data + i);
            list->head++;
        }
    }
}


void fifo_send(list_t *list)
{
    if (list != NULL_PTR)
    {
        while (list->tail != list->head)
        {
            uart_nmb_transmit(list->tail->data,10u);
            list->tail++;
        }    
    }
}