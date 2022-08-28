

MCU = ATmega328P
PORT = COM10
#PORT = /dev/ttyUSB0
PROGRAMMER = arduino

HAL_DIR = ../
GEN_DIR = ../../generic
HAL_INC_DIR =$(HAL_DIR)/inc
GEN_INC_DIR +=$(GEN_DIR)/gen_include
HAL_SRC_DIR = $(HAL_DIR)/src
GEN_SRC_DIR += $(GEN_DIR)/gen_src
USR_INC = ../../../../../../usr/include
TARGET_DIR = $(HAL_DIR)/target
INC_DIR = $(HAL_INC_DIR)

#install arduino software and take C:\Program Files (x86)\Arduino\hardware\tools\avr folder from there
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
CC = avr-gcc
DEBUG_LEVEL = -g
OPT = s
CFLAGS = -D GCC_MEGA_AVR -D F_CPU=16000000 -I$(INC_DIR) $(DEBUG_LEVEL) -O$(OPT) \
-fsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
$(WARNINGS) \
-Wa,-adhlns=$(<:.c=.lst) 
CFLAGS += -std=gnu99
OPTIMIZATION =
DEFINES = -DDEBUG
DEFINES += -D__AVR_ATmega328P__
OBJ_DIR=$(HAL_DIR)/target/obj
LDIR =$(HAL_DIR)/target/lib

LIBS  =-lm 
#Find all Source files withing the dir of the argument
#SRC_FILES =  $(HAL_SRC_DIR)/main.c
SRC_FILES += $(HAL_SRC_DIR)/gpio.c
SRC_FILES += $(HAL_SRC_DIR)/watchdog.c
SRC_FILES += $(HAL_SRC_DIR)/uart.c
SRC_FILES += $(HAL_SRC_DIR)/timer.c
SRC_FILES += $(HAL_SRC_DIR)/system.c
SRC_FILES += $(HAL_SRC_DIR)/isr.c


#Change ending .c to .o; Same Path!
OBJ_ENDING := ${SRC_FILES:.c=.o}

#OPTIMIZATION = -Og
#OPTIMIZATION = -O1
OPTIMIZATION = -O2
#OPTIMIZATION = -O3
ALL_CFLAGS += -mmcu=atmega328p -I. $(CFLAGS)
#Replace src file path with obj file path
OBJ_FILES := $(patsubst $(HAL_SRC_DIR)/%,$(OBJ_DIR)/%,$(OBJ_ENDING))

$(OBJ_DIR)/%.o: $(HAL_SRC_DIR)/%.c
	$(CC) -c $< $(ALL_CFLAGS) -o $@  $(OPTIMIZATION ) -g2 $(DEFINES) 

LDFLAGS = -Wl,-Map=$(TARGET).map,--cref

OBJCOPY_FLAGS = 
#
$(TARGET): $(OBJ_FILES)
	$(CC)  $(ALL_CFLAGS)  $(LIBS) $(LDFLAGS) $^ -o  $@.elf $(OPTIMIZATION ) -g2 $(DEFINES) $(OBJCOPY_FLAGS)
	${OBJCOPY} -O ihex ${TARGET}.elf ${TARGET}.hex
	${OBJDUMP} -h -s ${TARGET}.elf > ${TARGET}.lss

#hal: gccversion clean $(TARGET) flash

lib: $(OBJ_FILES)
	avr-ar rcs libatmega328p.a $(OBJ_FILES)

gccversion: 
	@$(CC) --version

#choose 57600 for arduino old bootloader 115200 for new bootloader
flash: 
	avrdude -p $(MCU) -b 115200 -c $(PROGRAMMER) -e -U flash:w:$(TARGET_DIR)/$(TARGET).hex  -F -P $(PORT)
.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET_DIR)/*.hex $(TARGET_DIR)/*.bin *~ core $(INCDIR)/*~ 
