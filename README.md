This is a playground of the development of examples targeted at the Arduino Uno (ATmega328P)  
to be used with the avr-gcc toolchain.

## Sources

* __blink_led_hw__ shows an example in the veins of __blink_led_sw__ to let the User LED  
  on the Arduino Uno blink once per second.  
  Although using a timer-based delay which is accomplished via an compare match event  
  of __TIMER1__.

* __blink_led_sw__ shows an example to let the User LED on the Arduino Uno blink once per  
  second.  
  The needed delay is accomplished via a software delay provided by `_delay_ms()` function.

* __hw_uart__ shows an interrupt controlled UART example using circular buffers as described  
  by Atmel Application Note [AVR306: Using the AVR UART in C] (http://www.atmel.com/atmel/acrobat/doc1451.pdf)

* __sw_uart__ shows an example of polled UART for basic input and output operation.  

## Schematics

### Board

<pre>
+-----------------------------------------------------------------------+
|                 AREF                                           TX RX  |
|                 [ ][ ][ ][ ][ ][ ][ ][ ]     [ ][ ][ ][ ][ ][ ][ ][ ] |
|                    GND                D8     D7             D2        |
|                                                                       |
|                                                                       |
|                                                                       |
|                                                                       |
|                                                                       |
|                                                                       |
|                                                                       |
|                                                                       |
|                                                                       |
|                                                              +-----+  |
|                                                              |[] []|  |
|                                                              |[] []|  |
|                                                              |[] []|  |
|                                                              +-ISP-+  |
|                                                                       |
|                             GND GND                                   |
|                 [ ] [ ] [ ] [ ] [ ] [ ]          [ ] [ ] [ ] [ ] [ ]  |
|                 RST 3V3 5V          Vin          A0              A5   |
+-----------------------------------------------------------------------+
</pre>

### Serial
A simple and cheap way to hookup the serial of the Arduino Uno Board is to use a USB to Serial  
cable like the Nokia CA-42. This cable is based on Prolific's PL-2303 chip and already  
provides a TTL converter.

<pre>
GND TX  RX
[ ] [ ] [ ]
 |   |   |
 |   |   |
 |   |   |                    ,~~~~~~~~~~~~'
 |   |   +----------[whi]----|             |
 |   +--------------[grn]----|             |
 +------------------[blu]----|             |
                              '------------'
                               Nokia CA-42
</pre>
