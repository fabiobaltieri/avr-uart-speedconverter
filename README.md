AVR UART Speed Converter
========================


This project is a small UART speed converter using an Atmel ATMega168
microcontroller.

The project was made to convert the UART data from a commercial GPS unit
working at 38400bps to the standard 4800 bps of NMEA 0183 data used by Nikon
DLSR cameras.

License
-------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Contents
--------

    COPYING     text version of the GPL
    README      this file
    firmware/   source directory for firmware files

Firmware
--------

Building requires an avr-gcc toolchain, in the firmware/ directory, to build
run:

    make

Flashing the firmware on the device requires avrdude and a compatible hardware
programmer. Default configuration is stored at the beginning of the Makefile.
To program with the default configuration, run:

    make load

Fuses can be configured running:

    make fuse 
