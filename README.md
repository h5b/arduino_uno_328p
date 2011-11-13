# arduino_uno_328p

This is a playground of the development of examples targeted  
at the Arduino Uno (ATmega328P) to be used with the avr-gcc  
toolchain.

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
