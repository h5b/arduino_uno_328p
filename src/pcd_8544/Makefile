PROG=main
SRCS=$(PROG).c \
     ${CURDIR}/pcd8544.c \
     $(SPI)/spi.c

SPI=	$(TOP)/sw_spi

CFLAGS+= -I${SPI}

include ${CURDIR}/../Makefile.inc
