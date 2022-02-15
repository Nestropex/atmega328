

MCU = ATmega328P
PORT = COM3
#PORT = /dev/ttyUSB0
PROGRAMMER = arduino

APP_DIR = ../
GEN_DIR = ../../generic
APP_INC_DIR =$(APP_DIR)/inc
GEN_INC_DIR +=$(GEN_DIR)/gen_include
APP_SRC_DIR = $(APP_DIR)/app_src
GEN_SRC_DIR += $(GEN_DIR)/gen_src
USR_INC = ../../../../../../usr/include
TARGET_DIR = $(APP_DIR)/target
INC_DIR = $(APP_INC_DIR)

#install arduino software and take C:\Program Files (x86)\Arduino\hardware\tools\avr folder from there
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
CC = avr-gcc
CFLAGS=-I$(INC_DIR)

OBJ_DIR=$(APP_DIR)/target/obj
LDIR =$(APP_DIR)/target/lib

LIBS  =-lm 
#Find all Source files withing the dir of the argument
SRC_FILES = $(APP_SRC_DIR)/main.c
SRC_FILES += $(APP_SRC_DIR)/gpio.c

#Change ending .c to .o; Same Path!
OBJ_ENDING := ${SRC_FILES:.c=.o}


#Replace src file path with obj file path
OBJ_FILES := $(patsubst $(APP_SRC_DIR)/%,$(OBJ_DIR)/%,$(OBJ_ENDING))

$(OBJ_DIR)/%.o: $(APP_SRC_DIR)/%.c
	$(CC) -c $< $(CFLAGS) -o $@

LDFLAGS = -Xlinker   -nostdlib 

OBJCOPY_FLAGS = -Wl -MAP=>output.map
#
$(TARGET): $(OBJ_FILES)
	$(CC)  $(CFLAGS) $(LIBS) $(LDFLAGS) $^ -o  $@.elf
	${OBJCOPY} -O ihex ${TARGET}.elf ${TARGET}.hex
	${OBJDUMP} -h -s ${TARGET}.elf > ${TARGET}.lss


flash: 
	avrdude -p $(MCU) -b 115200 -c $(PROGRAMMER) -e -U flash:w:$(TARGET_DIR)/$(TARGET).hex  -F -P $(PORT)
.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET_DIR)/*.hex $(TARGET_DIR)/*.bin *~ core $(INCDIR)/*~ 