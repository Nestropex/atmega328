PORT = COM11
BAUDRATE = 115200
MAKEFILE_DIR = target/generic

VARIANT = 328
MCU = ATmega$(VARIANT)P
TARGET = atmega$(VARIANT)
HAL_DIR = atmega$(VARIANT)p
APP_NAME = bldcdriver
APP_CFG_DEFINE = $(shell echo $(APP_NAME) | tr a-z A-Z)

DEFINES = -D__AVR_ATmega$(VARIANT)P__

CFLAGS = -D F_CPU=16000000 -mmcu=atmega$(VARIANT)p -D $(APP_CFG_DEFINE)


include target\generic/makefile
