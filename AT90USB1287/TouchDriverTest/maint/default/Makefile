###############################################################################
# Makefile for the project maint
###############################################################################

## General Flags
PROJECT = maint
MCU = at90usb1287
TARGET = maint.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -DNUM_X_LINES=8 -DNUM_Y_LINES=2 -DQT_NUM_CHANNELS=16 -DQT_DELAY_CYCLES=1 -DPORT_YA=C -D_ROTOR_SLIDER_ -D_QMATRIX_ -DNUM_X_PORTS=2 -DPORT_X_1=E -DPORT_X_2=C -DPORT_NUM_1=1 -DPORT_NUM_2=2 -DPORT_SMP=F -DSMP_PIN=5  -DQT_MAX_NUM_ROTORS_SLIDERS=2  -DPORT_YB=F   -DF_CPU=16000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += 


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Library Directories
LIBDIRS = -L"C:\Users\Tablet\nimron\Projects\P1000-Metis-NTNU_touch_module\trunk\firmware\driver-test\maint\." 

## Libraries
LIBS = -lavr51g2_16qm_8x_2y_krs_2rs 

## Objects that must be built in order to link
OBJECTS = maint.o touch.o qm_asm_tiny_mega.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) maint.hex maint.eep size

## Compile
maint.o: ../maint.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

touch.o: ../touch.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

qm_asm_tiny_mega.o: ../qm_asm_tiny_mega.S
	$(CC) $(INCLUDES) $(ASMFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) maint.elf dep/* maint.hex maint.eep

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

