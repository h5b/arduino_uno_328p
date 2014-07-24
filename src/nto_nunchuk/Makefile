PROG=	main

I2C=	$(TOP)/sw_i2c
UART=	$(TOP)/hw_uart

SRCS=	$(PROG).c \
	$(I2C)/i2c.c \
	$(UART)/uart.c \
	${CURDIR}/nunchuk.c

CFLAGS+= -I${I2C} -I${UART}

include ${CURDIR}/../Makefile.inc
