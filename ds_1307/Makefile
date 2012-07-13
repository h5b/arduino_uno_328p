include ../Makefile.inc

PROG=main
SRCS=$(PROG).c \
     ds1307.c \
     ../hw_uart/uart.c \
     ../sw_i2c/i2c.c \
     ../util/util.c

CLEANFILES=$(PROG).hex $(PROG).out

$(PROG).hex: $(PROG).out
	$(OBJCOPY) -O ihex $(PROG).out $(PROG).hex

$(PROG).out: $(SRCS) ../Makefile.inc
	$(CC) $(CPPFLAGS) $(CFLAGS) -I./ -o $(PROG).out $(SRCS)
	$(SIZE) $@

# enforce clean before programming to get current System Time
burn: clean $(PROG).hex
	$(AVR_DUDE) $(AVR_FLAGS) -e -U flash:w:$(PROG).hex

clean:
	rm -f $(CLEANFILES)
