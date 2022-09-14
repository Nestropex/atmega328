MCU = atmega328p
PORT = COM11
MAKEFILE_DIR = ../../generic/make

MCU = ATmega328P
TARGET = atmega328
HAL_DIR = ../../atmega328p
APP_NAME = bldc_driver


DEFINES += -D__AVR_ATmega328P__

DEBUG_LEVEL = -g
OPT = s
CFLAGS = -D GCC_MEGA_AVR -D F_CPU=16000000 -I$(INC_DIR) $(DEBUG_LEVEL) -O$(OPT) \
-fsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
$(WARNINGS) \
-Wa,-adhlns=$(<:.c=.lst) 
CFLAGS += -std=gnu99

ALL_CFLAGS += -mmcu=atmega328p -I. $(CFLAGS)
include $(MAKEFILE_DIR)/makefile
