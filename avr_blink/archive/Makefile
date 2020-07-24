#PROJECT NAME AVR_BLINK
#TARGET       ATMEL ATMEGA328P
#DATE MODIFIED 5/13/2020
#AUTHOR       NICK FRANGOS

#SETUP
MCU        = atmega328p
PROGRAMMER = usbtiny

#TOOLCHAIN
CC         = avr-gcc
OBJCOPY    = avr-objcopy
CFLAGS     = -Wall -g -Os -std=gnu99
CFLAGS    += -ffunction-sections -fdata-sections
LDFLAGS    = -Wl,-Map,$(TARGET).map
LDFLAGS   += -Wl,--gc-sections

#PROJECT
TARGET     = main
OBJECTS    = main.o
SOURCES    = main.c

#RULES
all: flash

flash: $(TARGET).hex
	avrdude -c $(PROGRAMMER) -p $(MCU) -U flash:w:$(TARGET).hex

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $> $@.hex

%.elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $(MCU) $^ -o $@

%.o: $(SOURCES)
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm -f *.o *.hex *.obj

.PHONY: dump
dump:
	avr-objdump -S $(OBJECTS) > $(OBJECTS).dump

.PHONY: flash
flash: $(TARGET).hex
	avrdude -p $(MCU) -c $(PROGRAMMER) -U flash:w:$(TARGET).hex

