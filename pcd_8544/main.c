/*
 * Copyright (c) 2012 Sebastian Trahm
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

#include "pcd8544.h"
#include "sw_spi/spi.h"

#define DISPLAY_CONTRAST	26
int
main(void)
{
	const char infoString[] = "Hello, World!";

	spiInit();
	pcd8544Init();
	pcd8544SetContrast(DISPLAY_CONTRAST);

	pcd8544SetXY(6, 2);
	pcd8544SmallStr(infoString);

	while (1) {
	}

	/* never reached */
	return 0;
}
