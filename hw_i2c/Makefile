include ../Makefile.inc

PROG=main
SRCS=$(PROG).c \
     ../hw_uart/uart.c \
     i2c.c

CLEANFILES=$(PROG).hex $(PROG).out

$(PROG).hex: $(PROG).out
	$(OBJCOPY) -O ihex $(PROG).out $(PROG).hex

$(PROG).out: $(SRCS) ../Makefile.inc
	$(CC) $(CPPFLAGS) $(CFLAGS) -I./ -o $(PROG).out $(SRCS)
	$(SIZE) $@

burn: $(PROG).hex
	$(AVR_DUDE) $(AVR_FLAGS) -e -U flash:w:$(PROG).hex

clean:
	rm -f $(CLEANFILES)
