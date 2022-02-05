
MAKEFILE_DIR = ../../generic/make

TARGET = stepper

AVR_HEADER = ../../../../../../../avr-libc
DEPS += $(USR_INC)
DEPS += $(APP_INC_DIR)
DEPS += $(AVR_HEADER)


include $(MAKEFILE_DIR)/makefile
