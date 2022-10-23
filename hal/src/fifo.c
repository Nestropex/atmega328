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

void fifo_init(void)
{
    msg_t message; 
    uint8_t size = sizeof(msg_t);

    uart_nmb_transmit(size,10u);
}