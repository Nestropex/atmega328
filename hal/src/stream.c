// Short description 
// The stream is thought to be the fifo that interacts with the hardware.
// i.e the uart tx stream keeps the data that needs to be send. Once the stream is filed
// with data, the first byte must be send triggered by software. After the transmit,
// an interrupt must occurre, the respective isr reads the next byte from the stream
// and transmits. This goes on until the stream is empty.
// In the meantime the general program can continue without any waiting time.
// Every peripheral must its own stream for rx and tx i.e. uart tx stream and rx stream
// or SPI rx stream and tx stream


//-------Includes-------

#include "datatypes.h"
#include "fifo.h"
#include "stream.h"
#include "uart.h"


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

    data = stream.tail->data;
    uart_fast_byte_transmit(&data);
    stream.tail++;}

void stream_read(list_t *list)
{

}