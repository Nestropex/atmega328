MCU = atmega328p
PORT = COM11
BAUDRATE = 115200
MAKEFILE_DIR = target/generic

MCU = ATmega328P
TARGET = atmega328
HAL_DIR = atmega328p
APP_NAME = bldcdriver
APP_CFG_DEFINE = $(shell echo $(APP_NAME) | tr a-z A-Z)

DEFINES = -D__AVR_ATmega328P__

CFLAGS = -D F_CPU=16000000 -mmcu=atmega328p -D $(APP_CFG_DEFINE)


include C:\Users\Nestropex1\Documents\GIT\atmega328\target\generic/makefile
