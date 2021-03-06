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

#ifndef _UART_H_
#define _UART_H_

#define UART_BUFFER_SIZE	32
#define UART_BUFFER_MASK	(UART_BUFFER_SIZE - 1)

static volatile unsigned char rxHead;
static volatile unsigned char rxTail;
static volatile unsigned char txHead;
static volatile unsigned char txTail;

/*
 * --- Head --,     --- Tail ----,
 *            |                  |
 * ,__________v________    ______v______,
 * | | | | | | | | | |  ..  | | | | | | |
 * `-------------------    -------------'
 * 0                                    UART_BUFFER_SIZE - 1
 */
static volatile unsigned char txBuffer[UART_BUFFER_SIZE];
static volatile unsigned char rxBuffer[UART_BUFFER_SIZE];

void uartInit(uint32_t);
void uartPutString(const char*);
void uartPutString_P(const char*);
void uartTransmitByte(unsigned char);
unsigned char uartReceiveByte(void);

#endif /* _UART_H_ */
