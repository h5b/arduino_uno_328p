# arduino_uno_328p

This is a collection of code targeted at the [Arduino Uno (ATmega328P)] (http://www.arduino.cc/en/Main/arduinoBoardUno)  
to be used with the AVR-GCC toolchain.

## Installation and Requirements

In order to ease the pain of setting up the development machine a Vagrantfile
is supplied. Make sure your machine has [VirtualBox](http://www.virtualbox.org)
and the [VirtualBox Extension Pack](http://download.virtualbox.org/virtualbox/4.2.18/) installed (to support USB
Programmers).

### Building your virtual environment

To bootstrap the virtual development machine you run the following commands:

```shell
git clone git@github.com:h5b/arduino_uno_328p.git
cd arduino_uno_328p
vagrant up
```

This sets up a virtual development machine host *avr-dev* based on Ubuntu
12.04. which you can login to by running:

`vagrant ssh`

The repository code lives in */vagrant* with user *vagrant* configured to be in
group *dialup* and udev configuration supplied to support the *AVRISP-MKII*.

## Board
![Arduino Uno ATmega328P](https://github.com/h5b/arduino_uno_328p/raw/master/doc/img/Uno328p.jpg)

## Sources

### Displays

* __pcd_8544__ implements an interface to the PCD8544 Display Controller used by Nokia's 3310 and 5110.

### Sensors

* __ds_1307__ implements an interface to the Dallas Maxim __DS1307__ Real-time Clock (RTC)  
  using the Software TWI (I2C) Master Mode. The Real-time Clock acts as Slave Device with  
  the clock information being sent to UART. For details regarding the DS1307 see [DS1307 Datasheet] (http://datasheets.maxim-ic.com/en/ds/DS1307.pdf).

* __ds_1631__ implements an interface to the Dallas Maxim __DS1631__ Temperature Sensor using the  
  Software TWI (I2C) Master Mode. The Temperature Sensor acts as Slave Device with the measured temperature being sent to UART.  
  For details regarding the DS1631 see [DS1631 Datasheet] (http://datasheets.maxim-ic.com/en/ds/DS1631-DS1731.pdf)  

### Timer

* __blink_led_hw__ is an example in the veins of __blink_led_sw__ to let the
  User LED of the Arduino Uno blink once per second. Although using a
  timer-based delay which is accomplished via an compare match event of __TIMER1__.

* __blink_led_sw__ implements an example to let the User LED of the Arduino Uno blink once per second.  
  The delay is accomplished via a software delay provided by _delay_ms() function.

### UART/I2C/SPI

* __hw_uart__ implements an interrupt controlled UART example using circular buffers as described  
  by Atmel Application Note [AVR306: Using the AVR UART in C] (http://www.atmel.com/atmel/acrobat/doc1451.pdf)

* __sw_uart__ is an example of polled UART for basic input and output operation.

* __sw_i2c__ implements software TWI (I2C) Master Mode.  

* __sw_spi__ implements a minimalized software SPI Master Mode.  

## Serial
A simple and cheap way to hookup the serial of the Arduino Uno Board to your Computer  
is to use a USB to Serial cable like the Nokia CA-42.  
It's based on Prolific's PL-2303 chip and already provides a TTL converter.

<pre>
GND TX  RX
[ ] [ ] [ ]
 |   |   |                   ,-------------.
 |   |   +----------[whi]----|             |
 |   +--------------[grn]----|             |
 +------------------[blu]----|             |
                             `-------------'
                               Nokia CA-42
</pre>
