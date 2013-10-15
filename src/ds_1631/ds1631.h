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

#ifndef _DS1631_H_
#define _DS1631_H_

/*
 * DS1631 - Circuitry
 *
 * .--------------=4k7=-----------.
 * | .------------=4k7=---------. |
 * | |                          | |
 * | |    ,____  ____.          | |
 * | '-1--|SDA `' VCC|--8-------`-`--> 3V3
 * '---2--|SCL     A0|--7----.
 *     3--|Tout    A1|--6----|
 *     4.-|GND     A2|--5----|
 *      | `----------'       |
 *      `--------------------`--| GND
 */

/*
 * DS1631 - Control Byte
 * ,-------------------------------------.
 * | 1 | 0 | 0 | 1 | A2 | A1 | A0 | R/_W |
 * `-------------------------------------'
 * 7                                     0
 */
#define DS1631_RD_ADDR		0x91
#define DS1631_WR_ADDR		0x90

/*
 * DS1631 - Command Set
 */
#define DS1631_RES_12BIT	0x0C /* 12 Bit Temperature Resolution */

#define DS1631_ACCESS_CFG	0xAC /* Access the configuration register */
#define DS1631_ACCESS_TH	0xA1 /* Access the high temperature register */
#define DS1631_ACCESS_TL	0xA2 /* Access the low temperature register */

#define DS1631_CONT_CONV	0xEE /* Continuous temperature conversion */
#define DS1631_POR		0x54 /* Initiate a software Power-On-Reset */

#define DS1631_READ_COUNT	0xA8 /* Read the counter register */
#define DS1631_READ_SLOPE	0xA9 /* Read the slope register */
#define DS1631_READ_TEMP	0xAA /* Read temperature register */
#define DS1631_START_CONV	0x51 /* Start temperature conversion */
#define DS1631_STOP_CONV	0x22 /* Stop temperature conversion */

#define DS1631_FRACTION(x)	( ((x) * 100) / 256 )

/*
 * DS1631 - 12-Bit Temperature Th(MSB) and Tl(LSB) Register Format
 *
 *     15                                                  8
 *     ,---------------------------------------------------.
 * MSB |  S   | 2^6  | 2^5  | 2^4  | 2^3 | 2^2 | 2^1 | 2^0 |
 *     `---------------------------------------------------'
 *     ,---------------------------------------------------.
 * LSB | 2^-1 | 2^-2 | 2^-3 | 2^-4 |  0  |  0  |  0  |  0  |
 *     `---------------------------------------------------'
 *     7                                                   0
 */

/*
 * DS1631 - 12-Bit Resolution Temperature/Data Relationship
 *
 * ,--------------.----------------------.---------.
 * | Temperature  | Binary               | Hex     |
 * |--------------.----------------------.---------|
 * | +125         | 0111 1101 0000 0000  | 0x7D00  |
 * |--------------.----------------------.---------|
 * | +25.0625     | 0001 1001 0001 0000  | 0x1910  |
 * |--------------.----------------------.---------|
 * | +10.125      | 0000 1010 0010 0000  | 0x0A20  |
 * |--------------.----------------------.---------|
 * | +0.5         | 0000 0000 1000 0000  | 0x0080  |
 * |--------------.----------------------.---------|
 * |  0           | 0000 0000 0000 0000  | 0x0000  |
 * |--------------.----------------------.---------|
 * | -0.5         | 1111 1111 1000 0000  | 0xFF80  |
 * |--------------.----------------------.---------|
 * | -10.125      | 1111 0101 1110 0000  | 0xF5E0  |
 * |--------------.----------------------.---------|
 * | -25.0625     | 1110 0110 1111 0000  | 0xE6F0  |
 * |--------------.----------------------.---------|
 * | -55          | 1100 1001 0000 0000  | 0xC900  |
 * `--------------'----------------------'---------'
 */

/*
 * DS1631 - Configuration Register
 *
 *     ,---------------------------------------------------.
 * MSB | DONE |  THF |  TLF |  NVB | R1  |  R0 | POL |1SHOT|
 *     `---------------------------------------------------'
 *     7                                                   0
 *
 *     DONE: Temperature Conversion Done
 *      THF: Temperature High Flag
 *      THL: Temperature Low Flag
 *      NVB: Non Volatile Memory Busy Flag
 *       R1: Resolution Bit 1
 *       R0: Resolution Bit 0
 *    1SHOT: Temperature Conversion Mode
 */

/*
 * DS1631 - Temperature Resolution Configuration
 *
 * ,----------------------------------------------,
 * | R1 | R0 | Resolution | Conversion Time (MAX) |
 * |----+----+------------+-----------------------|
 * | 0  | 0  |  9 Bit     |  93.75ms              |
 * |----+----+------------+-----------------------|
 * | 0  | 1  | 10 Bit     | 187.50ms              |
 * |----+----+------------+-----------------------|
 * | 1  | 0  | 11 Bit     | 375ms                 |
 * |----+----+------------+-----------------------|
 * | 1  | 1  | 12 Bit     | 750ms                 |
 * `----'----'------------'-----------------------'
 */

struct ds1631_temperature {
	unsigned char MSB;
	unsigned char LSB;
	unsigned char fraction;
};

extern struct ds1631_temperature ds1631_struct;

unsigned char ds1631GetRegister(unsigned char);
struct ds1631_temperature* ds1631GetTemperature(unsigned char);
void ds1631Init(void);
void ds1631WriteConfig(unsigned char, unsigned char);

#endif /* _DS1631_H_ */
