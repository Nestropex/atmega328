MCU = atmega328p
PORT = COM11
BAUDRATE = 115200
MAKEFILE_DIR = ../../generic/make

MCU = ATmega328P
TARGET = atmega328
HAL_DIR = ../../atmega328p
APP_NAME = bldc_driver


DEFINES += -D__AVR_ATmega328P__

DEBUG_LEVEL = -g
OPT = s
CFLAGS = -D F_CPU=16000000

ALL_CFLAGS += -mmcu=atmega328p -I. $(CFLAGS)
include $(MAKEFILE_DIR)/makefile
