include ../Makefile.inc

CHECK_SUITE=util_testrunner
CHECK_SRCS=$(CHECK_SUITE).c \
	   util.c

CLEANFILES=$(CHECK_SUITE)

check: $(CHECK_SUITE)
	@echo ",---------------------."
	@echo "| Running Unit Tests  |"
	@echo "'---------------------'"
	./$(CHECK_SUITE);
	@echo ""

$(CHECK_SUITE): $(CHECK_SRCS)
	$(CHECK_CC) $(CHECK_SRCS) $(CHECK_LIBS) -o $@

clean:
	rm -f $(CLEANFILES)

all:
	check
