
MAKEFILE_DIR = ../../generic/make

MCU = ATmega328P
TARGET = atmega328

AVR_HEADER = ../../../../../../../avr-libc
DEPS += $(USR_INC)
DEPS += $(APP_INC_DIR)
DEPS += $(AVR_HEADER)
HAL_DIR = ../../atmega328p
HAL_SRC_DIR = $(HAL_DIR)/src
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
CFLAGS = -D GCC_MEGA_AVR -D F_CPU=16000000 -I$(INC_DIR) $(DEBUG_LEVEL) -O$(OPT) \
-fsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
$(WARNINGS) \
-Wa,-adhlns=$(<:.c=.lst) 
CFLAGS += -std=gnu99

ALL_CFLAGS += -mmcu=atmega328p -I. $(CFLAGS)
include $(MAKEFILE_DIR)/makefile
