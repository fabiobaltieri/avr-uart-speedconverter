# Apps
CC	= avr-gcc
AS	= avr-as
LD	= avr-ld
OBJCOPY	= avr-objcopy
SIZE	= avr-size
GDB	= avr-gdb
AVRDUDE	= avrdude

# Options
MCU     = atmega168
CFLAGS	= -Os -Wall -mmcu=$(MCU)
ASFLAGS	= 
LDFLAGS	= 

AVRDUDEFLAGS = -c usbasp -p$(MCU)

# Fuse
HFUSE = 0xdd
LFUSE = 0xe2

targets	= main.elf main_text.hex main_eeprom.hex
objects	= main.o uart.o
deps	= Makefile defines.h

include Makefile.targets
