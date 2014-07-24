PROG=	main

I2C=	$(TOP)/sw_i2c
UART=	$(TOP)/hw_uart
UTIL=	$(TOP)/util

SRCS=	$(PROG).c \
	${CURDIR}/ds1631.c \
	$(I2C)/i2c.c \
	$(UART)/uart.c \
	$(UTIL)/util.c

CFLAGS+= -I${I2C} -I${UART} -I${UTIL}


include ${CURDIR}/../Makefile.inc
