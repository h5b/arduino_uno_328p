include ../Makefile.inc

PROG=main
SRCS=$(PROG).c

CLEANFILES=$(PROG).hex $(PROG).out

$(PROG).hex: $(PROG).out
	$(OBJCOPY) -j .text -O ihex $(PROG).out $(PROG).hex

$(PROG).out: $(SRCS) $(TOP)/Makefile.inc
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(PROG).out $(SRCS)
	$(SIZE) $@

burn: $(PROG).hex
	$(AVR_DUDE) $(AVR_FLAGS) -e -U flash:w:$(PROG).hex

clean:
	rm -f $(CLEANFILES)
