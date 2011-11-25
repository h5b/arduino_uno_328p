# arduino_uno_328p

This is a playground of the development of examples targeted  
at the Arduino Uno (ATmega328P) to be used with the avr-gcc  
toolchain.

## blink_led_hw
An example to let the User LED (PB5) on the Arduino Uno  
blink once per second.  
The needed delay is accomplished via compare match event  
of TIMER1.

## blink_led_sw
An example to let the User LED on the Arduino Uno blink  
once per second.  
The needed delay is accomplished via a software delay  
provided by <util/delay.h>.

## hw_uart
Interrupt controlled UART example using circular buffers as  
described by Atmel Application Note "AVR306: Using the AVR UART in C".

## soft_uart
Polled UART example for basic input and output operation.  

## Schematic

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
