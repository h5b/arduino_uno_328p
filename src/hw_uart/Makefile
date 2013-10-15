include ../Makefile.inc

PROG=main
SRCS=$(PROG).c \
     uart.c

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
