/*
 * Copyright (c) 2011-2012 Sebastian Trahm
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

#include "ds1631.h"
#include "../sw_i2c/i2c.h"
#include "../util/util.h"

struct ds1631_temperature ds1631_struct;

void
ds1631Init(void)
{
	unsigned char cfgREG;

	/* Read Config Register and Set 12 Bit Conversion */
	cfgREG = ds1631GetRegister(DS1631_ACCESS_CFG);
	cfgREG |= DS1631_RES_12BIT;
	i2cStart(DS1631_WR_ADDR);
	i2cWrite(DS1631_ACCESS_CFG);
	i2cWrite(cfgREG);
	i2cStop();

	ds1631WriteConfig(DS1631_WR_ADDR, DS1631_CONT_CONV);
	ds1631WriteConfig(DS1631_WR_ADDR, DS1631_START_CONV);
}

void
ds1631WriteConfig(unsigned char addr, unsigned char data)
{
	i2cStart(addr);
	i2cWrite(data);
	i2cStop();
}

struct ds1631_temperature*
ds1631GetTemperature(unsigned char addr)
{
	unsigned char temperatureMSB, temperatureLSB;

	ds1631WriteConfig(DS1631_WR_ADDR, DS1631_READ_TEMP);

	i2cStart(addr);
	temperatureMSB = i2cReadACK();
	temperatureLSB = i2cReadNAK();
	i2cStop();

	ds1631_struct.fraction = DS1631_FRACTION(temperatureLSB);
	ds1631_struct.MSB = temperatureMSB;
	ds1631_struct.LSB = temperatureLSB;

	return &ds1631_struct;
}

unsigned char
ds1631GetRegister(unsigned char cmd)
{
	unsigned char result;

	i2cStart(DS1631_WR_ADDR);
	i2cWrite(cmd);
	i2cStop();

	i2cStart(DS1631_RD_ADDR);
	result = i2cReadNAK();
	i2cStop();

	return result;
}
