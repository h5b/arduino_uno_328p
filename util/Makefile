include ../Makefile.inc

CHECK_SUITE=util_testrunner
CHECK_SRCS=$(CHECK_SUITE).c \
	   util.c

check: $(CHECK_SUITE)
	@echo ">> running unit tests <<"
	./$(CHECK_SUITE);

$(CHECK_SUITE): $(CHECK_SRCS)
	$(CHECK_CC) $(CHECK_SRCS) $(CHECK_LIBS) -o $@

all: check
