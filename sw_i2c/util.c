/*
 * Copyright (c) 2011 Sebastian Trahm
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

#include "uart.h"
#include "util.h"

/* output binary representation of integer to UART */
void
binrep(unsigned char val)
{
	int i = 0 ;

	for (i = (sizeof(val)*8)-1; i >= 0; i--)
		uartTransmitByte('0' + ((val >> i) & 1));
	uartPutString(": ");
}

/* convert unsigned integer to string */
void
uitoa(char* dest, char num)
{
	char c, *p = dest;

	if ((c = num / 100)) {
		num %= 100;
		*p++ = '0' + c;
	}

	if ((c = num / 10)) {
		num %= 10;
		*p++ = '0' + c;
	}

	*p++ = '0' + num;

	*p = '\0';
}
