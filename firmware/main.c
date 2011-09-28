/*
 * Copyright 2011 Fabio Baltieri (fabio.baltieri@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 */

#include "defines.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <string.h>
#include <avr/wdt.h>

#include "uart.h"

/*
 * circular buffer
 */

#define BUFSZ 960
volatile static char buffer[BUFSZ];
volatile static uint16_t buf_w, buf_r, buf_size;

static void buf_put (char c)
{
  if (buf_size < BUFSZ) {
    buffer[buf_w] = c;
    buf_w = (buf_w + 1) % BUFSZ;
    
    buf_size++;
  }
}

static char buf_get (void)
{
  char ret;

  if (buf_size > 0) {
    ret = buffer[buf_r];
    buf_r = (buf_r + 1) % BUFSZ;
    
    buf_size--;
  } else {
    ret = 0xff;
  }
  return ret;
}

static uint8_t buf_havedata (void)
{
  return (buf_size > 0);
}

/*
 * UART OUT
 */
volatile static uint8_t uout_counter;
volatile static uint8_t uout_data;

static void uout_init (void)
{
  uout_high();

  uout_counter = 0;

  /* timer 0, CTC mode*/
  TCCR0A = ( (1 << WGM01) | (0 << WGM00) );
  TCCR0B = ( (0 << WGM02) |
	     (0 << CS02) | (1 << CS01) | (0 << CS00) );

  /* prescaler = /8 */
  OCR0A = F_CPU / UOUT_SPEED / 8;
  TIMSK0 |= _BV(OCIE0A);
}

static uint8_t uout_idle (void)
{
  return (uout_counter == 0);
}

static void  uout_putchar (uint8_t ch)
{
  uout_data = ch;
  uout_counter = 10;
}

ISR(TIMER0_COMPA_vect)
{
  if (uout_counter == 0) {
    /* idle */
    uout_high();
  } else if (uout_counter == 1) {
    /* stop bit */
    uout_high();
    uout_counter--;
  } else if (uout_counter == 10) {
    /* start bit */
    uout_low();
    uout_counter--;
  } else {
    if (uout_data & 0x01)
      uout_high();
    else
      uout_low();
    uout_data >>= 1;
    uout_counter--;
  }

}

/*
 * Entry routine
 */
int main (void)
{
  MCUSR = 0;
  wdt_disable();

  /* leds */
  LED_DDR  |= _BV(LED_A);

  /* UART out -> drive, in -> pullup */
  UOUT_DDR |= _BV(UOUT);
  UIN_PORT |= _BV(UIN);
  
  buf_w = 0;
  buf_r = 0;
  buf_size = 0;

  uout_init();
  uart_init();

  sei();
  
  for (;;) {
    if (uart_poll()) {
      buf_put(uart_getchar());
    }
    
    if (buf_havedata() && uout_idle())
      uout_putchar(buf_get());
  }
  
  return 0;
}
