/*
 * Copyright (c) 2013-2014 Sebastian Trahm
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

#ifndef _NUNCHUK_H_
#define _NUNCHUK_H_

/*
 * Wii Nunchuk - Circuitry
 *
 *     ^
 *     |       ,__________.
 *     '---01--|GND    GND|--12-----[WH]---,     ,--------------------------.
 *       --02--|B1      A1|--11--           \____|                          |
 *  ,------03--|B2      A2|--10-----[YE]---------|                          |
 *  | ,----04--|B3      A3|--09-----[GN]---------|                          |
 *  | |  --05--|B4      A4|--08--          ,-----|                          |
 *  | | ,--06--|5V     3V3|--07-----[RS]---'     `--------------------------'
 *  | | |      `----------'                        Wii Nunchuk
 *  | | |         BSS138
 *  | | |
 *  | | |
 *  | | `--------------> 5V
 *  | |
 *  | `---------[SDA]--> PC4
 *  `-----------[SCL]--> PC5
 */

/*
 * Register Map and Protocol Information by WiiBrew (16/09/2012)
 * http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck
 */

/*
 * Wii Nunchuk - Register Map
 *
 *       ,-------------------------------------.
 *  0x00 |        X Position (Joystick)        |
 *       |-------------------------------------|
 *  0x01 |        Y Position (Joystick)        |
 *       |-------------------------------------|
 *  0x02 |        X Acceleration (Gyro)        | Bit 9..2
 *       |-------------------------------------|
 *  0x03 |        Y Acceleration (Gyro)        | Bit 9..2
 *       |-------------------------------------|
 *  0x04 |        Z Acceleration (Gyro)        | Bit 9..2
 *       |---------,---------,---------,---,---|
 *  0x05 | Z (1..0)| Y (1..0)| X (1..0)| C | Z |
 *       `---------'---------'---------'---'---'
 *       7                                     0
 */

#define NUNCHUK_BTN_C_FLAG	0x02
#define NUNCHUK_BTN_Z_FLAG	0x01
#define NUNCHUK_I2C_MSDELAY	10
#define NUNCHUK_REG_START	0x00
#define NUNCHUK_REG_SIZE	0x06

#define NUNCHUK_RD_ADDR		0xA5
#define NUNCHUK_WR_ADDR		0xA4

/* Normalized Nunchuk Sensor Data */
struct nunchuk_t {
	uint8_t joystickX;
	uint8_t joystickY;
	uint16_t accelX; /* MSB and LSB of 5th Byte */
	uint16_t accelY;
	uint16_t accelZ;
	uint8_t buttonZ;
	uint8_t buttonC;
};

void nunchukGetData(struct nunchuk_t*);
void nunchukInit(void);

#endif /* _NUNCHUK_H_ */
