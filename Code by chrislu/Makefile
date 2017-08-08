## General Flags
## 未完成
MCU = atmega128
CC = avr-gcc
CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99  -DF_CPU=11059200UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
# CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += -Wl,-u,vfprintf  -Wl,-u,vfscanf -Wl,-Map=$*.map

## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature
HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings

## Libraries
LIBS = -lm -lprintf_flt -lscanf_flt

## Objects that must be built in order to link
# OBJECTS = ASA_DIO.o ASA_SPI.o ASA_TMP121.o ASA_MAX7219.o

LIBSRC = $(wildcard TDK_Lib/*.c)
LIBOBJS = $(patsubst %.c,%.o,$(LIBSRC))

VPATH = Test TDK_Lib

## Objects explicitly added by the user
LINKONLYOBJECTS = ".\TDK_Lib\ASA_Lib.o"

## Build
help:
	@echo "use \"make {filename}.a\" to complie .c to .hex in dir ./hex"

## LIB OBJECTS Compile
ASA_DIO.o: ./LIB/ASA_DIO.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ASA_SPI.o: ./LIB/ASA_SPI.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ASA_TMP121.o: ./LIB/ASA_TMP121.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ASA_MAX7219.o: ./LIB/ASA_MAX7219.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
%.elf: %.o $(LIBOBJS)
	 $(CC) $(LDFLAGS) $< $(LIBOBJS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $@

%.hex: %.elf
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.a: %.elf %.hex
	@echo
	@avr-size -C --mcu=${MCU} $<
	@-mkdir -p hex
	@-mv $*.hex hex/
	@-rm -rf $(LIBOBJS) $*.map $*.o $<

%.eep: %.elf
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: %.elf
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(LIBOBJS) *.elf *.hex ./hex/*
