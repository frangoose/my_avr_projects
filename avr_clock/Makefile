#PROJECT NAME AVR_CLOCK
#TARGET       ATMEL ATMEGA328P
#DATE CREATED 5/14/2020
#AUTHOR       NICK FRANGOS

#SETUP
MCU        = atmega328p
PROGRAMMER = usbtiny

#TOOLCHAIN
CC         = avr-gcc
OBJCOPY    = avr-objcopy
CFLAGS     = -Wall -g -Os -std=gnu99
CFLAGS    += -ffunction-sections -fdata-sections -mmcu=$(MCU)
LDFLAGS    = -Wl,-Map,$(TARGET).map
LDFLAGS   += -Wl,--gc-sections -mmcu=$(MCU) 

#PROJECT
TARGET     = clock
ELF        = $(TARGET).elf
OBJECTS    = main.o TM1637.o USART.o
SOURCES    = main.c TM1637.c USART.c

#RULES
.PHONY: all
all: $(TARGET).hex

%.hex: $(ELF)
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

$(ELF): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $^

.PHONY: dump
dump:
	avr-objdump -S $(OBJECTS) > $(OBJECTS).dump

.PHONY: flash
flash: $(TARGET).hex
	sudo avrdude -c $(PROGRAMMER) -p $(MCU) -U flash:w:$(TARGET).hex

.PHONY: clean
clean:
	rm -f *.o *.dump *.elf *.map *.hex .s
