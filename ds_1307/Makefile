include ../Makefile.inc

PROG=main
SRCS=$(PROG).c \
     ds1307.c \
     i2c.c \
     uart.c

CLEANFILES=$(PROG).hex $(PROG).out $(CHECK_SUITE)

$(PROG).hex: $(PROG).out
	$(OBJCOPY) -O ihex $(PROG).out $(PROG).hex

$(PROG).out: $(SRCS) ../Makefile.inc
	$(CC) $(CPPFLAGS) $(CFLAGS) -I./ -o $(PROG).out $(SRCS)

# enforce clean before programming to get current System Time
burn: clean $(PROG).hex
	$(AVR_DUDE) $(AVR_FLAGS) -e -U flash:w:$(PROG).hex

clean:
	rm -f $(CLEANFILES)
