include ${CURDIR}/../Makefile.inc

PROG=main

SPI=	$(TOP)/sw_spi

SRCS=$(PROG).c \
     pcd8544.c \
     $(SPI)/spi.c

CFLAGS+= -I${SPI}

CLEANFILES=$(PROG).hex $(PROG).out

$(PROG).hex: $(PROG).out
	$(OBJCOPY) -O ihex $(PROG).out $(PROG).hex

$(PROG).out: $(SRCS) $(TOP)/Makefile.inc
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(PROG).out $(SRCS)
	$(SIZE) $@

burn: $(PROG).hex
	$(AVR_DUDE) $(AVR_FLAGS) -e -U flash:w:$(PROG).hex

clean:
	rm -f $(CLEANFILES)
