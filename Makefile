include Makefile.inc

SUBDIRS = blink_led_hw \
	  blink_led_sw \
	  ds_1307 \
	  ds_1631 \
	  hw_uart \
	  sw_uart \
	  sw_i2c \
	  util

all:
	for d in $(SUBDIRS); do $(MAKE) -C $$d; done

clean:
	for d in $(SUBDIRS); do $(MAKE) clean -C $$d; done
