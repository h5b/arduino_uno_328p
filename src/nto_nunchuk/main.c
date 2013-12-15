/*
 * Copyright (c) 2013 Sebastian Trahm
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
#include <math.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "board.h"
#include "i2c.h"
#include "nunchuk.h"
#include "uart.h"

#define BUFFER_SIZE	80

#define ACCEL_CALIB_X	500
#define ACCEL_CALIB_Y	500
#define ACCEL_CALIB_Z	500

#define WEIGHTING	0.0625

volatile int old_ax = 0;
volatile int old_ay = 0;
volatile int old_az = 0;

/* angles */
static inline int
nunchukGetRoll(struct nunchuk_tm* v)
{
	int ax = v->accelX - ACCEL_CALIB_X;
	int az = v->accelZ - ACCEL_CALIB_Z;

	/* simple low pass filter */
	ax = (ax * WEIGHTING) + (old_ax * (1.0 - WEIGHTING));
	az = (az * WEIGHTING) + (old_az * (1.0 - WEIGHTING));

	old_ax = ax;
	old_az = az;

	return (int) (atan2((double)ax, (double)az) * 180 / M_PI);
}

static inline int
nunchukGetPitch(struct nunchuk_tm* v)
{
	int ay = v->accelY - ACCEL_CALIB_Y;
	int az = v->accelZ - ACCEL_CALIB_Z;

	ay = (ay * WEIGHTING) + (old_ay * (1.0 - WEIGHTING));
	az = (az * WEIGHTING) + (old_az * (1.0 - WEIGHTING));

	old_ay = ay;
	old_az = az;

	return (int) (atan2((double)ay, (double)az) * 180 / M_PI);
}

int
main(void)
{
	struct nunchuk_tm* nunchuk = NULL;
	char buffer[BUFFER_SIZE];
	int roll = 0;
	int pitch = 0;

	i2cInit(I2C_STD_MODE);
	uartInit(BAUDRATE);
	sei();

	nunchukInit();

	/* initial read */
	nunchuk = nunchukGetData();
	old_ax = nunchuk->accelX;
	old_ay = nunchuk->accelY;
	old_az = nunchuk->accelZ;


	while (1) {
		nunchuk = nunchukGetData();
		roll = nunchukGetRoll(nunchuk);
		pitch = nunchukGetPitch(nunchuk);

		sprintf(buffer,
		    /* JSON data format */
		    "{\"x\":\"%03d\","
		    "\"y\":\"%03d\","
		    "\"r\":\"%04d\","
		    "\"p\":\"%04d\","
		    "\"c\":\"%d\","
		    "\"z\":\"%d\"}\r\n",
		    nunchuk->joystickX,
		    nunchuk->joystickY,
		    roll,
		    pitch,
		    nunchuk->buttonC,
		    nunchuk->buttonZ
		);
		uartPutString(buffer);
		_delay_ms(200);
	}

	/* never reached */
	return 0;
}
