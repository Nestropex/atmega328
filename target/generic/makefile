


#PORT = /dev/ttyUSB0
PROGRAMMER = arduino

APP_DIR = ../../app
GEN_DIR = ../../generic
HAL_INC_DIR = $(HAL_DIR)/inc
APP_INC_DIR = $(APP_DIR)/inc
GEN_INC_DIR +=$(GEN_DIR)/gen_include
HAL_SRC_DIR = $(HAL_DIR)/src
APP_SRC_DIR = $(APP_DIR)/src
GEN_SRC_DIR += $(GEN_DIR)/gen_src
USR_INC = ../../../../../../usr/include
HAL_TARGET_DIR = $(HAL_DIR)/target
TARGET_DIR = ../../target/$(APP_NAME)

INC_DIR = -I$(HAL_INC_DIR)
INC_DIR += -I$(APP_INC_DIR)

AVR_HEADER = ../../../../../../../avr-libc
DEPS += $(USR_INC)
DEPS += $(APP_INC_DIR)
DEPS += $(AVR_HEADER)
HAL_DIR = ../../hal
HAL_SRC_DIR = $(HAL_DIR)/src

OBJ_DIR=$(HAL_DIR)/target/obj
APP_OBJ_DIR=$(TARGET_DIR)/obj
LDIR =$(HAL_DIR)/target/lib
#install arduino software and take C:\Program Files (x86)\Arduino\hardware\tools\avr folder from there
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
OBJSIZE = avr-size
CC = avr-gcc
DEBUG_LEVEL = -g
OPT = s
CFLAGS += -D GCC_MEGA_AVR  $(INC_DIR) $(DEBUG_LEVEL) -O$(OPT) \
-fsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
$(WARNINGS)  -std=gnu99
DEFINES = -DDEBUG

HAL_LIB = $(HAL_TARGET_DIR)/lib$(TARGET).a
LIBS  =-lm -L$(HAL_LIB)
#Find all Source files withing the dir of the argument
APP_SRC_FILES +=  $(APP_SRC_DIR)/main.c
APP_SRC_FILES +=  $(APP_SRC_DIR)/$(APP_NAME).c
APP_SRC_FILES +=  $(APP_SRC_DIR)/period.c
SRC_FILES = $(HAL_SRC_DIR)/gpio.c
SRC_FILES += $(HAL_SRC_DIR)/watchdog.c
SRC_FILES += $(HAL_SRC_DIR)/uart.c
SRC_FILES += $(HAL_SRC_DIR)/timer.c
SRC_FILES += $(HAL_SRC_DIR)/system.c
SRC_FILES += $(HAL_SRC_DIR)/isr.c


#Change ending .c to .o; Same Path!
OBJ_ENDING := ${SRC_FILES:.c=.o}
APP_OBJ_ENDING := ${APP_SRC_FILES:.c=.o}

#OPTIMIZATION = -Og
#OPTIMIZATION = -O1
OPTIMIZATION = -O2
#OPTIMIZATION = -O3
ALL_CFLAGS += -mmcu=atmega328p -I. $(CFLAGS)
#Replace src file path with obj file path
OBJ_FILES := $(patsubst $(HAL_SRC_DIR)/%,$(OBJ_DIR)/%,$(OBJ_ENDING))
APP_OBJ_FILES := $(patsubst $(APP_SRC_DIR)/%,$(APP_OBJ_DIR)/%,$(APP_OBJ_ENDING))

$(OBJ_DIR)/%.o: $(HAL_SRC_DIR)/%.c
	$(CC) -c $< $(ALL_CFLAGS) -o $@  $(OPTIMIZATION ) -g2 $(DEFINES) 

$(APP_OBJ_DIR)/%.o: $(APP_SRC_DIR)/%.c 
	$(CC) -c $< $(ALL_CFLAGS) -o $@  $(OPTIMIZATION ) -g2 $(DEFINES) 
	
LDFLAGS = -Wl,-Map=$(TARGET).map,--cref

OBJCOPY_FLAGS = 

$(TARGET): $(APP_OBJ_FILES) $(HAL_LIB)
	$(CC)  $(ALL_CFLAGS)  $(LIBS) $(LDFLAGS) $^ -o  $@.elf $(OPTIMIZATION ) -g2 $(DEFINES) $(OBJCOPY_FLAGS)
	${OBJCOPY} -O ihex ${TARGET}.elf ${TARGET}.hex
	${OBJDUMP} -h -s ${TARGET}.elf > ${TARGET}.lss
	$(OBJSIZE) -C --mcu=$(MCU)  $(TARGET).elf

all: gccversion clean_all lib $(TARGET)  flash
app: gccversion clean_app $(TARGET) flash
hal: gccversion clean_all lib

lib: $(OBJ_FILES)
	avr-ar rcs $(HAL_LIB) $(OBJ_FILES)

gccversion: 
	@$(CC) --version

#choose 57600 for arduino old bootloader 115200 for new bootloader
flash: 
	avrdude -p $(MCU) -b $(BAUDRATE) -c $(PROGRAMMER) -e -U flash:w:$(TARGET_DIR)/$(TARGET).hex  -F -P $(PORT)
.PHONY: clean

clean_hal:
	rm -f $(OBJ_DIR)/*.o  $(HAL_TARGET_DIR)/*.a *~ core $(INCDIR)/*~ 
clean_app:
	rm -f $(APP_OBJ_DIR)/*.o $(APP_TARGET_DIR)/*.hex $(APP_TARGET_DIR)/*.bin *~ core $(INCDIR)/*~ 
clean_all: clean_hal clean_app
