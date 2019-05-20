################################################################################
# Project Settings
################################################################################

# Name of the target (files will be named like that)
PROJECT=avr-simracing-buttonbox

OBJECTS  = main.o
OBJECTS += uart.o
OBJECTS += flipswitch.o
OBJECTS += rotary_encoder.o
OBJECTS += util.o
OBJECTS += event_handler.o
#OBJECTS += usbdrv/usbdrv.o 
#OBJECTS += usbdrv/usbdrvasm.o 
#OBJECTS += usbdrv/oddebug.o



################################################################################
# Microcontroller Settings
################################################################################

# Name of the Microcontroller
MCU=atmega32

# Clock of the Microcontroller (Hz)
F_CPU=16000000

# Fuses
L_FUSE=0xFF
H_FUSE=0xD9
E_FUSE=0xFF



################################################################################
# Progammer Settings
################################################################################
PROGRAMMER=usbasp
#PORT=-P/dev/ttyS0
#BAUD=-B115200


AVRDUDE = avrdude -p $(MCU) $(PORT) $(BAUD) -c $(PROGRAMMER) 



################################################################################
# Compiler Settings
################################################################################

CFLAGS += -Os
CFLAGS += -Wall
CFLAGS += -fpack-struct
CFLAGS += -fshort-enums
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections
CFLAGS += -std=gnu99
CFLAGS += -funsigned-char
CFLAGS += -funsigned-bitfields
CFLAGS += -DF_CPU=$(F_CPU)UL
CFLAGS += -Iusbdrv
CFLAGS += -I.


COMPILE = avr-gcc $(CFLAGS) -mmcu=$(MCU)

################################################################################
# Linker Settings
################################################################################

LDFLAGS = 

LINK = avr-gcc $(LDFLAGS) -mmcu=$(MCU)



################################################################################
# Main rules
################################################################################

all: clean hex eeprom flash_hex

list_targets: 
	avr-gcc --target-help

hex: clean $(PROJECT).hex size

eeprom: $(PROJECT)_eeprom.hex

size:
	avr-size --mcu=$(MCU) -C $(PROJECT).elf

flash_hex:
	$(AVRDUDE) -U flash:w:$(PROJECT).hex:a

read_fuses:
	$(AVRDUDE) -U lfuse:r:-:i

flash_fuses:
	$(AVRDUDE) -U lfuse:w:$(L_FUSE):m -U hfuse:w:$(H_FUSE):m -U efuse:w:$(E_FUSE):m

clean:
	rm -rf *.o
	rm -rf *.elf
	rm -rf *.hex
	rm -rf usbdrv/*.o



################################################################################
# Rule for generating a hex-file from an elf-file
################################################################################
$(PROJECT).hex: $(PROJECT).elf
	avr-objcopy -O ihex -j .data -j .text $(PROJECT).elf $(PROJECT).hex


################################################################################
# Rule for generating a eeprom-file from an elf-file
################################################################################
$(PROJECT)_eeprom.hex: $(PROJECT).elf
	avr-objcopy -O ihex -j .eeprom --change-section-lma .eeprom=1 $(PROJECT).elf $(PROJECT)_eeprom.hex


################################################################################
# Rule for generating a elf-file from all compiled object files
################################################################################
$(PROJECT).elf: $(OBJECTS)
	$(LINK) $(OBJECTS) -o $(PROJECT).elf


################################################################################
# Generic rule for compiling C files:
################################################################################
.c.o:
	$(COMPILE) -c $< -o $@


################################################################################
# Generic rule for assembling Assembler source files:
################################################################################
.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@


################################################################################
# Generic rule for compiling C to assembler, used for debugging only.
################################################################################
.c.s:
	$(COMPILE) -S $< -o $@

