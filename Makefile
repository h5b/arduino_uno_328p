include Makefile.inc

SUBDIRS = blink_led_hw \
	  blink_led_sw \
	  hw_uart \
	  sw_uart

all:
	for d in $(SUBDIRS); do $(MAKE) -C $$d; done

clean:
	for d in $(SUBDIRS); do $(MAKE) clean -C $$d; done
