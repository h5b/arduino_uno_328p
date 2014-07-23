AVR_DUDE = avrdude
AVR_MMCU = m328p
AVR_PROG = avrispmkII

AVR_FLAGS = -c $(AVR_PROG) -P usb -p $(AVR_MMCU)

MCU	= atmega328p
CLOCK	= 16000000

CC	= avr-gcc
OBJCOPY	= avr-objcopy
OBJDUMP	= avr-objdump
SIZE	= avr-size -C --mcu=$(MCU)

OPT	= s

# Common Include Paths
TOP := $(dir $(lastword $(MAKEFILE_LIST)))
TOP := $(patsubst %/, %, $(TOP))
EXTRAINCDIRS = -I$(TOP) -I.
CPPFLAGS += $(EXTRAINCDIRS)

CPPFLAGS+= -D__AVR_ATmega328P__
CPPFLAGS+= -DF_CPU=${CLOCK}

CFLAGS += -mmcu=$(MCU) -O$(OPT)
CFLAGS += -fpack-struct
CFLAGS += -funsigned-bitfields
CFLAGS += -funsigned-char
CFLAGS += -Wall
CFLAGS += -Wcast-align
CFLAGS += -Werror
CFLAGS += -Wextra
CFLAGS += -Wimplicit
CFLAGS += -Wpointer-arith
CFLAGS += -Wredundant-decls
CFLAGS += -Wreturn-type
CFLAGS += -Wshadow
CFLAGS += -Wswitch
CFLAGS += -Wunused

CLEANFILES=$(PROG).hex $(PROG).out

$(PROG).out: $(SRCS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(PROG).out $(SRCS)
	@echo "___ [SIZE] _____________________________________________"
	$(SIZE) $@
	@echo "___ [SIZE] _____________________________________________"

$(PROG).hex: $(PROG).out
	$(OBJCOPY) -O ihex $(PROG).out $(PROG).hex

burn: clean $(PROG).hex
	$(AVR_DUDE) $(AVR_FLAGS) -e -U flash:w:$(PROG).hex

clean:
	rm -f $(CLEANFILES)
