# arduino_uno_328p

This project is targeted at the development of various code examples for the
[Arduino Uno (ATmega328P)] (http://www.arduino.cc/en/Main/arduinoBoardUno)
using plain C with the AVR-GCC toolchain while automating the setup process of
a development environment with VirtualBox and Vagrant.

![Arduino Uno ATmega328P](https://github.com/h5b/arduino_uno_328p/raw/master/doc/img/Uno328p.jpg)

## Requirements

* [VirtualBox](https://www.virtualbox.org)
* [VirtualBox Extension Pack](http://download.virtualbox.org/virtualbox/)
* [Vagrant](http://vagrantup.com)

### Bootstrapping the Virtual Development Machine

```
git clone https://github.com/h5b/arduino_uno_328p.git
cd arduino_uno_328p
git submodule init
git submodule update
vagrant up
```

This sets up a virtual development machine host __avr-dev__ based on Ubuntu
12.04. with the AVR-GCC toolchain already being installed.
The setup takes a couple of minutes. After the installation has finished you
can login to the machine by running: `vagrant ssh`

## Code Examples

* [pcd_8544](https://github.com/h5b/arduino_uno_328p/tree/master/src/pcd_8544)
  implements an interface to the PCD8544 Display Controller used by Nokia's
  3310 and 5110 using SPI in Master Mode.

* [ds_1307](https://github.com/h5b/arduino_uno_328p/tree/master/src/ds_1307)
  implements an interface to the Dallas Maxim DS1307 Real-time Clock (RTC)
  using the Software TWI (I2C) Master Mode. The Real-time Clock acts as
  Slave Device with the clock information being sent to UART.
  For details see the
  [DS1307 Datasheet](http://datasheets.maxim-ic.com/en/ds/DS1307.pdf).

* [ds_1631](https://github.com/h5b/arduino_uno_328p/tree/master/src/ds_1631)
  implements an interface to the Dallas Maxim DS1631 Temperature Sensor
  using the Software TWI (I2C) Master Mode. The Temperature Sensor acts as
  Slave Device with the measured temperature being sent to UART.
  For details see the
  [DS1631 Datasheet](http://datasheets.maxim-ic.com/en/ds/DS1631-DS1731.pdf).

* [nto_nunchuk](https://github.com/h5b/arduino_uno_328p/tree/master/src/nto_nunchuk)
  implements an interface to the Nunchuk Controller by Nintendo using Software
  TWI (I2C) Master Mode. The sensor values are used to calculate the Pitch and
  Roll Angle with a very simple low-pass filter to smooth the output. Angles,
  the X- and Y-Axis of the joystick and the state of the two buttons being sent
  to UART as JSON string. As the Nunchuk expects 3V3 Level on I2C Bus a
  bi-directional Logic Level Converter is used to connect with Atmega328P's 5V.
  For details see
  [nunchuk.h](https://github.com/h5b/arduino_uno_328p/blob/master/src/nto_nunchuk/nunchuk.h)
  which contains the schematic.

* [blink_led_hw](https://github.com/h5b/arduino_uno_328p/tree/master/src/blink_led_hw)
  is an example in the veins of
  [blink_led_sw](https://github.com/h5b/arduino_uno_328p/tree/master/src/blink_led_sw)
  to let the User LED of the Arduino Uno blink once per second. Although using
  a timer-based delay which is accomplished via an compare match event of
  TIMER1.

* [blink_led_sw](https://github.com/h5b/arduino_uno_328p/tree/master/src/blink_led_sw)
  implements an example to let the User LED of the Arduino Uno blink once per
  second. The delay is accomplished via a software delay provided by the
  _delay_ms() function.

* [hw_uart](https://github.com/h5b/arduino_uno_328p/tree/master/src/hw_uart)
  implements an interrupt controlled UART example using circular buffers as
  described by Atmel Application Note
  [AVR306: Using the AVR UART in C](http://www.atmel.com/atmel/acrobat/doc1451.pdf).

* [sw_uart](https://github.com/h5b/arduino_uno_328p/tree/master/src/sw_uart)
  is an example of polled UART for basic input and output operation.

* [sw_i2c](https://github.com/h5b/arduino_uno_328p/tree/master/src/sw_i2c)
  implements software TWI (I2C) Master Mode.

* [sw_spi](https://github.com/h5b/arduino_uno_328p/tree/master/src/sw_spi)
  implements a minimalized software SPI Master Mode.

### Running Code Examples

The following steps show how to run the
[blink_led_hw](https://github.com/h5b/arduino_uno_328p/tree/master/src/blink_led_hw)
example:

```
vagrant ssh
cd /vagrant/src/blink_led_hw
make burn
```
