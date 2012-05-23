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

#include "util.h"

/* Convert binary coded decimal to decimal */
char
bcd2dec(char val)
{
	 return ((val/16 * 10) + (val % 16));
}

/* Convert decimal to binary coded decimal */
char
dec2bcd(char val)
{
	return ((val/10 * 16) + (val % 10));
}

/* Convert unsigned integer to string */
void
uitoa(char* dest, unsigned char num)
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
