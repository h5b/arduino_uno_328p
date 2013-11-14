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

#include <avr/io.h>

#include <util/delay.h>

#include "i2c.h"
#include "nunchuk.h"

struct nunchuk_tm nunchukData;

static inline uint8_t
nunchukDecodeByte(uint8_t val)
{
	return ((val ^ 0x17) + 0x17);
}

static inline void
nunchukSetReadPointer(void)
{
	i2cStart(NUNCHUK_WR_ADDR);
	i2cWrite(NUNCHUK_REG_START);
	i2cStop();
	_delay_ms(NUNCHUK_I2C_MSDELAY);
}

struct nunchuk_tm*
nunchukGetData(void)
{
	uint8_t i = 0;
	uint8_t regs[NUNCHUK_REG_SIZE];

	/* Initialize Read Pointer Address - mandatory! */
	nunchukSetReadPointer();

	i2cStart(NUNCHUK_RD_ADDR);
	for (i = 0; i < sizeof(regs) - 1; i++ ) {
		regs[i] = i2cReadACK();
	}
	regs[sizeof(regs)-1] = i2cReadNAK();
	i2cStop();

	for (i = 0; i < sizeof(regs); i++) {
		regs[i] = nunchukDecodeByte(regs[i]);
	}

	nunchukData.joystickX = regs[0];
	nunchukData.joystickY = regs[1];
	nunchukData.buttonZ = !(regs[5] & NUNCHUK_BTN_Z_FLAG);
	nunchukData.buttonC = !(regs[5] & NUNCHUK_BTN_C_FLAG);
	/* MSB and extracted LSB Bit of accelerometer */
	nunchukData.accelX = ((regs[2] << 2) | ((regs[5] >> 2) & 0x03));
	nunchukData.accelY = ((regs[3] << 2) | ((regs[5] >> 4) & 0x03));
	nunchukData.accelZ = ((regs[4] << 2) | ((regs[5] >> 6) & 0x03));


	return &nunchukData;
}

void
nunchukInit(void)
{
	i2cStart(NUNCHUK_WR_ADDR);
	i2cWrite(0x40);
	i2cWrite(NUNCHUK_REG_START);
	i2cStop();
	_delay_ms(NUNCHUK_I2C_MSDELAY);
}
