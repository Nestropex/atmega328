
MAKEFILE_DIR = ../../generic/make

TARGET = atmega328

AVR_HEADER = ../../../../../../../avr-libc
DEPS += $(USR_INC)
DEPS += $(APP_INC_DIR)
DEPS += $(AVR_HEADER)


include $(MAKEFILE_DIR)/makefile
