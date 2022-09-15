MCU = atmega328p
PORT = COM11
BAUDRATE = 115200
MAKEFILE_DIR = ../generic

MCU = ATmega328P
TARGET = atmega328
HAL_DIR = ../../atmega328p
APP_NAME = coilwind
APP_CFG_DEFINE = $(shell echo $(APP_NAME) | tr a-z A-Z)

DEFINES += -D__AVR_ATmega328P__

DEBUG_LEVEL = -g
OPT = s
CFLAGS = -D F_CPU=16000000 -D $(APP_CFG_DEFINE)

ALL_CFLAGS += -mmcu=atmega328p -I. $(CFLAGS)
include $(MAKEFILE_DIR)/makefile
