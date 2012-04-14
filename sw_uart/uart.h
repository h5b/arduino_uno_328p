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

#ifndef _UART_H_
#define _UART_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define BAUDRATE 9600
/* calculate the Baudrate Register Value based on F_CPU and BAUDRATE */
#define UBRR_VAL ((F_CPU + BAUDRATE * 8L) / ((BAUDRATE * 16L) - 1))

void uartInit(void);
unsigned char uartReceiveByte(void);
void uartTransmitByte(unsigned char);
void uartPutString(const char*);
void uartPutString_P(const char*);

#endif /* _UART_H_ */
