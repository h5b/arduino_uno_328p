include ../Makefile.inc

PROG=main
SRCS=$(PROG).c \
     ds1631.c \
     ../hw_uart/uart.c \
     ../sw_i2c/i2c.c \
     ../util/util.c

CHECK_SUITE=util_testrunner
CHECK_SRCS=$(CHECK_SUITE).c \
	   util.c

CLEANFILES=$(PROG).hex $(PROG).out $(CHECK_SUITE)

$(PROG).hex: $(PROG).out
	$(OBJCOPY) -O ihex $(PROG).out $(PROG).hex

$(PROG).out: $(SRCS) ../Makefile.inc
	$(CC) $(CPPFLAGS) $(CFLAGS) -I./ -o $(PROG).out $(SRCS)

burn: $(PROG).hex
	$(AVR_DUDE) $(AVR_FLAGS) -e -U flash:w:$(PROG).hex

check: $(CHECK_SUITE)
	@echo ">> running unit tests <<"
	./$(CHECK_SUITE);

$(CHECK_SUITE): $(CHECK_SRCS)
	$(CHECK_CC) $(CHECK_SRCS) $(CHECK_LIBS) -o $@

clean:
	rm -f $(CLEANFILES)
