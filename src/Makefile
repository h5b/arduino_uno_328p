SUBDIRS = blink_led_hw \
	  blink_led_sw \
	  ds_1307 \
	  ds_1631 \
	  hw_uart \
	  nto_nunchuk \
	  pcd_8544 \
	  sw_uart \
	  util

all:
	for d in $(SUBDIRS); do $(MAKE) -C $$d; done

clean:
	for d in $(SUBDIRS); do $(MAKE) clean -C $$d; done
