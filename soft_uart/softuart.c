#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define BAUDRATE 9600
/* calculate the Baudrate Register Value based on F_CPU and BAUDRATE */
#define UBRR_VAL ((F_CPU + BAUDRATE * 8L) / ((BAUDRATE * 16L) - 1))

void
uartInit(void)
{
	/* set Baud Rate Register */
	UBRR0H = (unsigned int)(UBRR_VAL >> 8);
	UBRR0L = (unsigned int)(UBRR_VAL);
	/* enable UART receive and transmit */
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	/* MODE: ASYNC 8N1 */
	UCSR0C = (3<<UCSZ00);
}

unsigned char
uartReceiveByte(void)
{
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void
uartTransmitByte(unsigned char data)
{
	while (!(UCSR0A&(1 << UDRE0)));
	UDR0 = data;
}

void
uartPutString_P(const char *addr)
{
	unsigned char c;

	while ((c = pgm_read_byte(addr++)))
		uartTransmitByte(c);
}

int
main(void)
{
	static const char infostring[] PROGMEM = "SOFT-UART Demo\r\n";

	uartInit();
	uartPutString_P(infostring);

	while (1) {
		/* do nothing */
	}

	/* never reached */
	return 0;
}
