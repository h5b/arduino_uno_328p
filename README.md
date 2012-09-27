This is a playground of the development of examples targeted at the [Arduino Uno (ATmega328P)] (http://www.arduino.cc/en/Main/arduinoBoardUno)  
to be used with the AVR-GCC toolchain.

## Board
![Arduino Uno ATmega328P](https://github.com/h5b/arduino_uno_328p/raw/master/doc/img/Uno328p.jpg)

## Sources

* __blink_led_hw__ is an example in the veins of __blink_led_sw__ to let the User LED  
  of the Arduino Uno blink once per second. Although using a timer-based delay which is  
  accomplished via an compare match event of __TIMER1__.

* __blink_led_sw__ implements an example to let the User LED of the Arduino Uno blink once per  
  second. The delay is accomplished via a software delay provided by `_delay_ms() function.

* __ds_1307__ implements an interface to the Dallas Maxim __DS1307__ Real-time Clock (RTC)  
  using the Software TWI (I2C) Master Mode. The Real-time Clock acts as Slave Device with the  
  clock information being sent to UART.  
  For details regarding the DS1307 see [DS1307 Datasheet] (http://datasheets.maxim-ic.com/en/ds/DS1307.pdf).

* __ds_1631__ implements an interface to the Dallas Maxim __DS1631__ Temperature Sensor  
  using the Software TWI (I2C) Master Mode. The Temperature Sensor acts as Slave Device with  
  the measured temperature being sent to UART.  
  For details regarding the DS1631 see [DS1631 Datasheet] (http://datasheets.maxim-ic.com/en/ds/DS1631-DS1731.pdf)  

* __hw_uart__ implements an interrupt controlled UART example using circular buffers as described  
  by Atmel Application Note [AVR306: Using the AVR UART in C] (http://www.atmel.com/atmel/acrobat/doc1451.pdf)

* __sw_i2c__ implements software TWI (I2C) Master Mode.  

* __sw_spi__ implements a minimalized software SPI Master Mode.  

* __sw_uart__ is an example of polled UART for basic input and output operation.  

## Schematics

### Board

<pre>
,-----------------------------------------------------------------------.
|                    GND                                         TX RX  |
|                 [ ][ ][ ][ ][ ][ ][ ][ ]     [ ][ ][ ][ ][ ][ ][ ][ ] |
|                AREF   PB5            PB0     PD7                  PD0 |
|                                                                       |
|                                                                       |
|                                                                       |
|                                                                       |
|                                                                       |
|                                                            +-ISP-+    |
|                                                           1| o o |6   |
|                                                           2| o o |5   |
|                                                           3| o o |4   |
|                                                            +-----+    |
|                                                                       |
|                                                                       |
|                                                                       |
|                                                                       |
|                                                                       |
|                             GND GND                          SDA SCL  |
|                 [ ] [ ] [ ] [ ] [ ] [ ]          [ ] [ ] [ ] [ ] [ ]  |
|                 RST 3V3 5V          Vin          PC0             PC5  |
`-----------------------------------------------------------------------'

ICSP-Header
----------
1) MISO
2) SCK
3) SET
4) GND
5) MOSI
6) Vcc

</pre>

### Serial
A simple and cheap way to hookup the serial of the Arduino Uno Board to your Computer  
is to use a USB to Serial cable like the Nokia CA-42.  
It's based on Prolific's PL-2303 chip and already provides a TTL converter.

<pre>
GND TX  RX
[ ] [ ] [ ]
 |   |   |
 |   |   |
 |   |   |                   ,-------------.
 |   |   +----------[whi]----|             |
 |   +--------------[grn]----|             |
 +------------------[blu]----|             |
                             `-------------'
                               Nokia CA-42
</pre>
