/*
 * Copyright (c) 2011-2013 Sebastian Trahm
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <util/delay.h>

#include "board.h"
#include "ds1631.h"
#include "i2c.h"
#include "uart.h"

#define BUFFER_SIZE	36

/*
 * The DS1631 provides three configurable address pins which allow
 * up to eight addresses and therefore devices on the same bus.
 * In this example all address bits are connected to ground
 * (see schematic in header file) leading to Base Address 0x91.
 */
#define THERMO_ADDR	0x91

int
main(void)
{
	struct ds1631_t ds1631_sensor;
	ds1631_sensor.addr = THERMO_ADDR;

	static const char infostring[] PROGMEM = "Demo - DS1631 Thermometer\r\n";
	char buffer[BUFFER_SIZE];

	uartInit(BAUDRATE);
	i2cInit(I2C_FAST_MODE);
	ds1631Init(&ds1631_sensor);
	sei();

	uartPutString_P(infostring);

	while (1) {
		ds1631ReadSensor(&ds1631_sensor);

		sprintf(buffer, "[TEMP: %03d] [TH: %03d] [TL: %03d]\r\n",
		    ds1631_sensor.val, ds1631_sensor.msb, ds1631_sensor.lsb);

		uartPutString(buffer);
		_delay_ms(1000);
	}

	/* never reached */
	return (0);
}
