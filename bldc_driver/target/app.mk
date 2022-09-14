
MAKEFILE_DIR = ../../generic/make

MCU = ATmega328P
TARGET = atmega328
HAL_DIR = ../../atmega328p
APP_DIR = ../../bldc_driver
#Find all Source files withing the dir of the argument
SRC_FILES += $(HAL_SRC_DIR)/gpio.c
SRC_FILES += $(HAL_SRC_DIR)/watchdog.c
SRC_FILES += $(HAL_SRC_DIR)/uart.c
SRC_FILES += $(HAL_SRC_DIR)/timer.c
SRC_FILES += $(HAL_SRC_DIR)/system.c
SRC_FILES += $(HAL_SRC_DIR)/isr.c

DEFINES += -D__AVR_ATmega328P__

DEBUG_LEVEL = -g
OPT = s
CFLAGS = -D F_CPU=16000000
CFLAGS += -std=gnu99

ALL_CFLAGS += -mmcu=atmega328p -I. $(CFLAGS)
include $(MAKEFILE_DIR)/makefile
