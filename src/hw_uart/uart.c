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

/*
 * Simplified interrupt controlled UART using circular buffers as described
 * by Atmel Application Note "AVR306: Using the AVR UART in C".
 */

#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "board.h"
#include "uart.h"

void
uartInit(uint32_t baudrate)
{
	/*
	 * UBRR - Uart Baud Rate Register
	 * UBRR = System Clock / Baud Rate * 16 - 1
	 */
	uint8_t ubrr = ((F_CPU + baudrate * 8L) / (baudrate * 16L) - 1);

	/* set Baud Rate Register */
	UBRR0H = (unsigned int)(ubrr >> 8);
	UBRR0L = (unsigned int)(ubrr);

	/* enable Receive, Transmit and Complete Interrupt Enable */
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	UCSR0B |= (1<<TXCIE0) | (1<<RXCIE0);

	/* MODE: ASYNC 8N1 */
	UCSR0C = (3<<UCSZ00);

	rxHead = 0;
	rxTail = 0;
	txHead = 0;
	txTail = 0;
}

unsigned char
uartReceiveByte(void)
{
	unsigned char data;
	unsigned char tmptail;

	/* just return if no data available */
	if (rxHead == rxTail)
		return (0);

	/* calculate and save new buffer index */
	tmptail = ((rxTail + 1) & UART_BUFFER_MASK);
	rxTail = tmptail;

	/* return data from receive buffer */
	data = rxBuffer[tmptail];

	/* enable Receive interrupt */
	UCSR0B |= (1<<RXCIE0);

	return data;
}

void
uartTransmitByte(unsigned char data)
{
	unsigned char tmphead;

	tmphead = ((txHead + 1) & UART_BUFFER_MASK);

	/* wait until space in buffer is available */
	while (tmphead == txTail) {
		;
	}

	txBuffer[tmphead] = data;
	txHead = tmphead;

	/* enable UDRE interrupt to transmit data */
	UCSR0B |= (1<<UDRIE0);
}

void
uartPutString(const char *str)
{
	unsigned char c;

	while ((c = *str++))
		uartTransmitByte(c);
}

void
uartPutString_P(const char *addr)
{
	unsigned char c;

	while ((c = pgm_read_byte(addr++)))
		uartTransmitByte(c);
}

ISR
(USART_RX_vect)
{
	unsigned char data;
	unsigned char tmphead;

	data = UDR0;

	/* calculate buffer index */
	tmphead = ((rxHead + 1) & UART_BUFFER_MASK);

	/* buffer overflow detected */
	if (tmphead == rxTail ) {
		/* disable Receive interrupt */
		UCSR0B &= ~(1<<RXCIE0);
		return;
	} else {
		/* save new index */
		rxHead = tmphead;
		/* save received data in buffer */
		rxBuffer[tmphead] = data;
	}
}

ISR
(USART_UDRE_vect)
{
	unsigned char tmptail;

	if (txHead != txTail) {
		/* calculate and Save buffer index */
		tmptail = ((txTail + 1) & UART_BUFFER_MASK);
		txTail = tmptail;
		/* retrieve Byte from buffer and pass it to UART */
		UDR0 = txBuffer[tmptail];
	} else {
		/* no data available, therefore disable UDRE interrupt */
		UCSR0B &= ~(1<<UDRIE0);
	}
}

ISR
(USART_TX_vect)
{
	PORTB ^= (USER_LED);
}
